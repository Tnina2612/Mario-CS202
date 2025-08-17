#include<level/Level.hpp>
#include<fstream>
#include<unordered_map>
#include<string>
#include<filesystem>
#include<core/Program.hpp>
#include<scenes/PlayScene.hpp>
#include<scenes/DeathScene.hpp>
#include<scenes/GameOverScene.hpp>
#include<scenes/TitleScene.hpp>
#include<scenes/TimeUpScene.hpp>
#include<diy_functions/read.h>

EnemyManager::EnemyManager(std::string filename, SubLevel* subLevel) :
    subLevel(subLevel) {
    EnemyFactory::loadAllFrames();
    ifstream inp(filename);

    int numTypes;
    readFromFile(inp, filename, numTypes);

    for(int i = 0; i < numTypes; i++) {
        int numEnemies;
        readFromFile(inp, filename, numEnemies);

        string enemyType;
        readFromFile(inp, filename, enemyType);

        if(enemyType != "Bowser") {
            for(int j = 0; j < numEnemies; j++) {
                float x, y; 
                readFromFile(inp, filename, x, y);

                list.push_back(EnemyFactory::createEnemy(enemyType, Vector2{x, y}, this));
                list.back()->setActive(true);
            }
        } else {
            for(int j = 0; j < numEnemies; j++) {
                float x, y;
                readFromFile(inp, filename, x, y);

                listBowsers.push_back(make_shared<Bowser>("Bowser", Vector2{x, y}, subLevel->player));
                listBowsers.back()->setActive(true);
            }
        }
    }
    inp.close();
}

void EnemyManager::addEnemy(std::shared_ptr<Enemy> enemy) {
    spawnQueue.push(enemy);
}

Vector2 EnemyManager::getPlayerPos() const {
    return subLevel->player->getPos();
}

void EnemyManager::update() {
    if(subLevel->player->getGrowthUp() == true || subLevel->player->getShrinkDown() == true) {
        return;
    }

    // if(IsKeyPressed(KEY_SPACE)) {
    //     oke = !oke;
    // }
    // if(!oke) {
    //     return;
    // }
    std::vector<CharacterFireball*> fires = subLevel->player->getFireballs();
    for(auto& enemy : list) {
        // Check if the enemy is off-screen
        if(enemy->getPos().x < 0 || enemy->getPos().y - enemy->getHitBox().height > Global::ORIGINAL_HEIGHT) {
            continue;
        }
        
        // Check if the enemy is alive and within the camera view
        if(enemy->getPos().x < subLevel->camera->target.x + Global::ORIGINAL_WIDTH / 2) {
            subLevel->blocks->update(enemy);
            enemy->update();
            for(auto& enemy2 : list) {
                if(enemy != enemy2 && enemy->isAlive() && enemy2->isAlive() && CheckCollisionRecs(enemy->getHitBox(), enemy2->getHitBox())) {
                    // if(enemy->getPos().x < enemy2->getPos().x) {
                    //     enemy->hitBlockRight();
                    //     enemy2->hitBlockLeft();
                    // } else {
                    //     enemy->hitBlockLeft();
                    //     enemy2->hitBlockRight();
                    // }
                    enemy->onEnemyCollision(*enemy2);
                    enemy2->onEnemyCollision(*enemy);
                }
            }
        }
        
        for(auto& f : fires) {
            subLevel->blocks->update(enemy, f);
        }
    }

    for(auto& bowser : listBowsers) {
        bowser->update();
    }

    while(!spawnQueue.empty()) {
        auto enemy = spawnQueue.front();
        spawnQueue.pop();
        list.push_back(enemy);
    }
}

void EnemyManager::updatePlayer() {
    for(auto& enemy : list){
        Rectangle pastPlayerRec = subLevel->playerManager.gameplayManager.pastPlayerRec;
        if(CheckCollisionRecs(enemy->getHitBox(), subLevel->player->getRectangle()) && enemy->isAlive()) {
            if(pastPlayerRec.y + pastPlayerRec.height < enemy->getHitBox().y && 
                enemy->getTypeName().find("Plant") == std::string::npos) {
                enemy->hitUp();
                subLevel->player->setVeclocityY(-100);
                Program::getInstance().getHUD().onNotify(EventType::ADDSCORE);
            } else {
                int dir = enemy->getPos().x < subLevel->player->getPos().x ? 1 : -1;
                enemy->hitVertical(dir);
                subLevel->player->takeDamage();
            }
        }
    }
}

void EnemyManager::draw() const {
    for(const auto& enemy : list) {
        enemy->draw();
    }
    for(const auto& bowser : listBowsers) {
        bowser->draw();
    }
}

void EnemyManager::saveToFile(std::string filename) {
    ofstream out(filename);
    out << list.size() << endl;
    std::vector<std::string> enemyTypes = EnemyFactory::getEnemyTypesNames();
    for(const auto& type : enemyTypes) {
        int count = 0;
        for(const auto& enemy : list) {
            if(enemy->getTypeName() == type && enemy->isAlive()) {
                count++;
            }
        }
        out << count << " " << type << endl;
        for(const auto& enemy : list) {
            if(enemy->getTypeName() == type && enemy->isAlive()) {
                Vector2 pos = enemy->getPos();
                out << pos.x << " " << pos.y << endl;
            }
        }
    }
    out.close();
}