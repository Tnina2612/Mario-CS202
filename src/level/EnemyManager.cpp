#include<level/Level.hpp>
#include<fstream>
#include<unordered_map>
#include<string>

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
        for(int j = 0; j < numEnemies; j++) {
            float x, y; 
            inp >> x >> y;
            list.push_back(EnemyFactory::createEnemy(enemyType, Vector2{x, y}));
            list.back()->setActive(true);
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
        if(CheckCollisionRecs(enemy->getHitBox(), subLevel->player->getRectangle())) {
            float overlapX = std::min(enemy->getHitBox().x + enemy->getHitBox().width, subLevel->player->getRectangle().x + subLevel->player->getRectangle().width) - std::max(enemy->getHitBox().x, subLevel->player->getRectangle().x);
            float overlapY = std::min(enemy->getHitBox().y, subLevel->player->getRectangle().y) - std::max(enemy->getHitBox().y - enemy->getHitBox().height, subLevel->player->getRectangle().y - subLevel->player->getRectangle().height);
            if(overlapY < overlapX) {
                if(subLevel->player->getPos().y < enemy->getPos().y) {
                    enemy->onStomp();
                } else {
                    subLevel->player->die();
                }
            } else {
                subLevel->player->die();
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