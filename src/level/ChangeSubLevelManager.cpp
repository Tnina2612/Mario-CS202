#include<level/Level.hpp>

ChangeSubLevelManager::ChangeSubLevelManager(std::string filename, SubLevel* subLevel) : subLevel(subLevel) {
    ifstream inp(filename);
    int numPoints;
    inp >> numPoints;
    list.resize(numPoints);
    for(int i = 0; i < numPoints; i++) {
        float x, y, width, height;
        inp >> x >> y >> width >> height;
        list[i].detectRec = Rectangle{x, y, width, height};
        inp >> list[i].key;
        addAnimation(i, inp);
        inp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        string filename;
        getline(inp, filename);
        if(filename != "None") {
            string worldType;
            inp >> worldType;
            inp >> x >> y;
            list[i].nextScene = make_shared<NextSubLevelScene>(NextSubLevelScene{filename, worldType, Vector2{x, y}});
        }
    }
    inp.close();
}

void ChangeSubLevelManager::update() {
    for(int id = 0; id < (int)list.size(); id++) {
        if(okToChange(id)) {
            transit(id);
            break;
        }
    }
}

void ChangeSubLevelManager::addAnimation(int id, ifstream& inp) {
    int numAnimations;
    inp >> numAnimations;
    for(int i = 0; i < numAnimations; i++) {
        string type;
        inp >> type;
        if(type == "Down") {
            list[id].animations.push_back(make_shared<PlayerDownPipeAnimation>());
        } else if(type == "Up") {
            float targetY;
            inp >> targetY;
            list[id].animations.push_back(make_shared<PlayerUpPipeAnimation>(targetY));
        } else if(type == "Left") {
            list[id].animations.push_back(make_shared<PlayerIntoLeftPipeAnimation>());
        } else if(type == "Right") {
            list[id].animations.push_back(make_shared<PlayerIntoRightPipeAnimation>());
        } else if(type == "ClimbDown") {
            float targetY;
            inp >> targetY;
            list[id].animations.push_back(make_shared<PlayerClimbDownAnimation>(list[id].detectRec.x, targetY));
        } else if(type == "WalkToX") {
            float targetX;
            inp >> targetX;
            list[id].animations.push_back(make_shared<PlayerWalkToXAnimation>(targetX, subLevel->blocks.get()));
        } else if(type == "EnterDoor") {
            list[id].animations.push_back(make_shared<PlayerEnterDoorAnimation>());
        } else if(type == "ExitDoor") {
            list[id].animations.push_back(make_shared<PlayerExitDoorAnimation>()); 
        }
        else {
            throw runtime_error("Unknown animation type: " + type);
        }
    }
}

bool ChangeSubLevelManager::okToChange(int id) {
    if(list[id].key == "Down" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec) && IsKeyPressed(KEY_DOWN)) return true;
    if(list[id].key == "Left" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec) && IsKeyPressed(KEY_LEFT)) return true;
    if(list[id].key == "Right" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec) && IsKeyPressed(KEY_RIGHT)) return true;
    if(list[id].key == "Up" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec) && IsKeyPressed(KEY_UP)) return true;
    if(list[id].key == "Touch" && CheckCollisionRecs(subLevel->player->getRectangle(), list[id].detectRec)) return true;
    if(list[id].key == "Disappear" && CheckCollisionPointRec(subLevel->player->getPos(), list[id].detectRec) && subLevel->player->getScale() <= 0.1f) return true;
    return false;
}

void ChangeSubLevelManager::transit(int id) {
    subLevel->playerManager.addAnimation(make_unique<SubLevelPlayerAnimationManager>(subLevel, list[id].animations, list[id].nextScene));
}

void ChangeSubLevelManager::draw() const {
    for(const ChangeSubLevelPoint& point : list) {
        DrawRectangleRec(point.detectRec, Color{50, 50, 100, 100});
        DrawText(point.key.c_str(), point.detectRec.x + 5, point.detectRec.y + 5, 10, WHITE);
    }
}