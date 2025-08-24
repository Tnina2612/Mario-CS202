#include<level/Level.hpp>
#include<limits>
#include<diy_functions/read.h>
#include<string>

PlayerAnimationManager::PlayerAnimationManager(std::string filename, SubLevel* subLevel) : subLevel(subLevel) {
    ifstream inp(filename);
    if(inp.is_open() == false) {
        throw std::runtime_error("PlayerAnimationManager::PlayerAnimationManager(filename, subLevel): Cannot open file " + filename + "\n");
    }

    int numPoints;
    readFromFile(inp, filename, numPoints);
    
    list.resize(numPoints);
    for(int i = 0; i < numPoints; i++) {
        float x, y, width, height;
        readFromFile(inp, filename, x, y, width, height);
        list[i].detectRec = Rectangle{x, y, width, height};
        
        readFromFile(inp, filename, list[i].key);

        addAnimation(i, inp);

        inp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        string levelFolder;
        getline(inp, levelFolder);
        if(inp.fail()) {
            throw std::runtime_error("Failed to read filename in PlayerAnimationManager::PlayerAnimationManager(filename, subLevel)\n");
        }

        if(levelFolder != "None") {
            string worldType;
            readFromFile(inp, filename, worldType, x, y);
            
            list[i].nextScene = make_shared<NextSubLevelScene>(NextSubLevelScene{levelFolder, worldType, Vector2{x, y}});
        }
    }
    inp.close();
}

void PlayerAnimationManager::update() {
    if(inAnimation() == true) {
        todoAnimation.front()->update();
        
        if(todoAnimation.front()->isDone() == true) {
            todoAnimation.pop();

            if(todoAnimation.empty() == true && toNextScene != nullptr) {
                subLevel->level->changeSubLevel(*toNextScene);
            }
        }
    } else {
        if(subLevel->player->getGrowthUp()) {
            todoAnimation.push(make_shared<PlayerGrowAnimation>());
            todoAnimation.back()->initialize(subLevel->player);
        }

        if(subLevel->player->getShrinkDown()) {
            todoAnimation.push(make_shared<PlayerShrinkAnimation>());
            todoAnimation.back()->initialize(subLevel->player);
        }

        for(int id = 0; id < (int)list.size(); id++) {
            if(okToChange(id)) {
                transit(id);
                break;
            }
        }
    }
}

void PlayerAnimationManager::addAnimation(int id, ifstream& inp) {
    std::string filename = "playerAnimationPoints.txt";

    int numAnimations;
    readFromFile(inp, filename, numAnimations);
    
    for(int i = 0; i < numAnimations; i++) {
        string type;
        readFromFile(inp, filename, type);

        if(type == "Down") {
            list[id].animations.push_back(make_shared<PlayerDownPipeAnimation>());
        } else if(type == "Up") {
            float targetY;
            readFromFile(inp, filename, targetY);
            
            list[id].animations.push_back(make_shared<PlayerUpPipeAnimation>(targetY));
        } else if(type == "Left") {
            list[id].animations.push_back(make_shared<PlayerIntoLeftPipeAnimation>());
        } else if(type == "Right") {
            list[id].animations.push_back(make_shared<PlayerIntoRightPipeAnimation>());
        } else if(type == "ClimbDown") {
            float targetY;
            bool directionAfterClimbIsRight;
            readFromFile(inp, filename, targetY, directionAfterClimbIsRight);

            list[id].animations.push_back(make_shared<PlayerClimbDownFlagColumnAnimation>(list[id].detectRec.x, targetY, directionAfterClimbIsRight));
        } else if(type == "WalkToX") {
            float targetX;
            readFromFile(inp, filename, targetX);
            list[id].animations.push_back(make_shared<PlayerWalkToXAnimation>(targetX, subLevel->blocks.get()));
        } else if(type == "EnterDoor") {
            list[id].animations.push_back(make_shared<PlayerEnterDoorAnimation>());
        } else if(type == "ExitDoor") {
            list[id].animations.push_back(make_shared<PlayerExitDoorAnimation>()); 
        } else if(type == "Wait") {
            float waitTime;
            readFromFile(inp, filename, waitTime);

            list[id].animations.push_back(make_shared<PlayerWaitAnimation>(waitTime));
        } else if(type == "Win") {
            list[id].animations.push_back(make_shared<PlayerWinAnimation>());
        }
        else {
            throw runtime_error("Unknown animation type: " + type);
        }
    }
}

bool PlayerAnimationManager::okToChange(int id) {
    if(list[id].key == "Down" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec) && IsKeyPressed(KEY_DOWN)) return true;
    if(list[id].key == "Left" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec) && IsKeyDown(KEY_LEFT)) return true;
    if(list[id].key == "Right" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec) && IsKeyDown(KEY_RIGHT)) return true;
    if(list[id].key == "Up" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec) && IsKeyPressed(KEY_UP)) return true;
    if(list[id].key == "Touch" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec)) return true;
    if(list[id].key == "Disappear" && CheckCollisionPointRec(subLevel->player->getPos(), list[id].detectRec) && subLevel->player->getAnimation().getScale() <= 0.1f) return true;
    return false;
}

void PlayerAnimationManager::transit(int id) {
    for(int i = 0; i < (int)list[id].animations.size(); i++) {
        todoAnimation.push(list[id].animations[i]);
        todoAnimation.back()->initialize(subLevel->player);
    }

    if(list[id].nextScene != nullptr) {
        toNextScene = list[id].nextScene;
    }
}

void PlayerAnimationManager::draw() const {
    for(const PlayerAnimationPoint& point : list) {
        DrawRectangleRec(point.detectRec, Color{50, 50, 100, 100});
        DrawText(point.key.c_str(), point.detectRec.x + 5, point.detectRec.y + 5, 10, WHITE);
    }
}

void PlayerAnimationManager::saveToFile(std::string filename) const {
    ofstream out(filename);
    out << list.size() << endl;
    for(const PlayerAnimationPoint& point : list) {
        out << point.detectRec.x << " " << point.detectRec.y << " " 
            << point.detectRec.width << " " << point.detectRec.height << " "
            << point.key << endl;
        out << point.animations.size() << endl;
        for(auto animation : point.animations) {
            animation->saveToFile(out);
            out << endl;
        }
        if(point.nextScene) {
            out << point.nextScene->filename << endl;
            out << point.nextScene->worldType << endl;
            out << point.nextScene->newPlayerPosition.x << " " << point.nextScene->newPlayerPosition.y << endl;
        } else {
            out << "None" << endl;
        }
    }
    out.close();
}

bool PlayerAnimationManager::inAnimation(void) const {
    return todoAnimation.size() > 0;
}