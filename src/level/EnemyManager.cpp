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

EnemyManager::EnemyManager(std::string filename, SubLevel* subLevel) :
    subLevel(subLevel) {
    EnemyFactory::loadAllFrames();
    ifstream inp(filename);
    int numTypes;
    inp >> numTypes;
    for(int i = 0; i < numTypes; i++) {
        int numEnemies;
        inp >> numEnemies;
        string enemyType;
        inp >> enemyType;
        if(enemyType != "Bowser") {
            for(int j = 0; j < numEnemies; j++) {
                float x, y; 
                inp >> x >> y;
                list.push_back(EnemyFactory::createEnemy(enemyType, Vector2{x, y}));
                list.back()->setActive(true);
            }
        } else {
            
        }
    }
    inp.close();
}

void EnemyManager::update() {
    for(auto& enemy : list){
        // Check if the enemy is off-screen
        if(enemy->getPos().x < 0 || enemy->getPos().y - enemy->getHitBox().height > Global::ORIGINAL_HEIGHT) {
            continue;
        }

        // Check if the enemy is alive and within the camera view
        if(enemy->getPos().x < subLevel->camera->target.x + Global::ORIGINAL_WIDTH / 2) {
            enemy->update();
            subLevel->blocks->update(enemy);
            for(auto& enemy2 : list) {
                if(enemy != enemy2 && enemy->isAlive() && enemy2->isAlive() && CheckCollisionRecs(enemy->getHitBox(), enemy2->getHitBox())) {
                    if(enemy->getPos().x < enemy2->getPos().x) {
                        enemy->hitBlockRight();
                        enemy2->hitBlockLeft();
                    } else {
                        enemy->hitBlockLeft();
                        enemy2->hitBlockRight();
                    }
                }
            }
        }

        // Check for collisions with the player
        Rectangle pastPlayerRec = subLevel->playerManager.gameplayManager.pastPlayerRec;
        if(CheckCollisionRecs(enemy->getHitBox(), subLevel->player->getRectangle()) && enemy->isAlive()) {
            if(pastPlayerRec.y + pastPlayerRec.height < enemy->getHitBox().y && 
                enemy->getTypeName().find("Plant") == std::string::npos) {
                enemy->onStomp();
                subLevel->player->setVeclocityY(-100);
                Program::getInstance().getHUD().onNotify(EventType::ADDSCORE);
            } else {
                subLevel->player->die();
                // if(subLevel->player->getNumLives() > 0) {
                //     Program::getInstance().pushScene(new DeathScene());
                // } else {
                //     cout << "Game Over! You have no lives left." << endl;
                //     Program::getInstance().pushScene(new GameOverScene());
                // }
                Program::getInstance().pushScene(new DeathScene());
                if (Program::getInstance().getSession().LIVES == 0) {
                    Program::getInstance().pushScene(new GameOverScene());
                    Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
                    Program::getInstance().getHUD().onNotify(EventType::RESET_LIVES);
                    Program::getInstance().getHUD().onNotify(EventType::RESET_SCORES);
                }
                Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
            }
        }
    }
}

void EnemyManager::draw() const {
    for(const auto& enemy : list) {
        enemy->draw();
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