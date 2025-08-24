#include<level/Level.hpp>
#include<fstream>
#include<unordered_map>
#include<string>
#include<filesystem>
#include<cmath>
#include<core/Program.hpp>
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

EnemyManager::EnemyManager(const EnemyManager& o) {
    if(this == &o) return;

    for(int i = 0; i < (int)o.list.size(); i++) {
        shared_ptr<Enemy> enemy = o.list[i];
        if(enemy == nullptr) {
            throw runtime_error("EnemyManager copy constructor: o.list[i] is nullptr\n");
        }

        list.push_back(EnemyFactory::createEnemy(enemy->getTypeName(), enemy->getPos(), this));
        list.back()->setActive(true);
    }

    std::queue<std::shared_ptr<Enemy>> _spawnQueue = o.spawnQueue;
    while(_spawnQueue.size() > 0) {
        shared_ptr<Enemy> enemy = _spawnQueue.front();
        _spawnQueue.pop();

        spawnQueue.push(EnemyFactory::createEnemy(enemy->getTypeName(), enemy->getPos(), this));
    }

    for(int i = 0; i < (int)o.listBowsers.size(); i++) {
        shared_ptr<Bowser> bowser = o.listBowsers[i];
        listBowsers.push_back(make_shared<Bowser>("Bowser", bowser->getPos(), nullptr));
    }
}

void EnemyManager::connectToSubLevel(SubLevel* subLevel) {
    this->subLevel = subLevel;
    
    for(shared_ptr<Bowser> bowser : listBowsers) {
        bowser->connectToPlayer(subLevel->player);
    }

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
                    enemy->onEnemyCollision(*enemy2);
                    enemy2->onEnemyCollision(*enemy);
                }
            }
        }
        

        for(auto& f : fires) {
            checkCollisionsEnemyFireball(enemy, f);
        }
    }
    
    for(auto& bowser : listBowsers) {
        bowser->update();
        checkCollisionsPlayerBowser(subLevel->player, bowser.get());
        checkCollisionsPlayerFireballBowser(subLevel->player, bowser.get());
        for(auto& f : fires) {
            checkCollisionsFireballPlayerBowser(f, bowser.get());
        }
    }

    while(!spawnQueue.empty()) {
        auto enemy = spawnQueue.front();
        spawnQueue.pop();
        list.push_back(enemy);
    }
}

void EnemyManager::updatePlayer() {
    for(auto& enemy : list) {
        if (!enemy->isAlive()) continue;

        Rectangle pastPlayerRec = subLevel->playerManager->gameplayManager.pastPlayerRec;
        Rectangle pastEnemyRec  = enemy->getPastRect();
        
        if(CheckCollisionRecs(enemy->getHitBox(), subLevel->player->getRectangle()) && enemy->isAlive()) {
            std::cerr << "Y: " << pastPlayerRec.y + pastPlayerRec.height - enemy->getHitBox().y << std::endl;
            
            if(subLevel->player->getIsStarMan()) {
                enemy->onHit();
                Program::getInstance().getHUD().onNotify(EventType::ADDSCORE, subLevel->player->getPos());
                continue;
            }

            // rollBackFrames(subLevel->player, enemy.get(), pastPlayerRec);
            if(pastPlayerRec.y + pastPlayerRec.height < enemy->getHitBox().y &&
                enemy->getTypeName().find("Plant") == std::string::npos) 
            {
                enemy->hitUp();
                subLevel->player->setVeclocityY(-200);
                Program::getInstance().getHUD().onNotify(EventType::ADDSCORE, subLevel->player->getPos());
            } else {
                int dir = enemy->getPos().x < subLevel->player->getPos().x ? 1 : -1;
                
                if(!enemy->beHitVertical()) {
                    subLevel->player->takeDamage();
                } else {
                    enemy->hitVertical(dir);
                }
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

void EnemyManager::checkCollisionsPlayerBowser(Character* player, Bowser* bowser) {
    if(CheckCollisionRecs(player->getRectangle(), bowser->getHitBoxes()[0])) {
        if(!bowser->isAlive()) {
            return;
        }
        player->takeDamage();
    }
}

void EnemyManager::checkCollisionsPlayerFireballBowser(Character* player, Bowser* bowser) {
    for(int i = 1; i < bowser->getHitBoxes().size(); i++) {
        if(CheckCollisionRecs(player->getRectangle(), bowser->getHitBoxes()[i])) {
            player->takeDamage();
            bowser->fireballs[i - 1]->setActive(false);
        }
    }
}

void EnemyManager::checkCollisionsFireballPlayerBowser(CharacterFireball* fire, Bowser* bowser) {
    if(CheckCollisionRecs(fire->getHitBox(), bowser->getHitBoxes()[0])) {
        if(fire->getActive())
            bowser->beHitByFireball();
        fire->hitBlockHorizontal();
    }
}

Bowser * EnemyManager::getBowser(void) {
    if(listBowsers.empty()) return nullptr;
    return listBowsers[0].get();
}

void EnemyManager::checkCollisionsEnemyFireball(std::shared_ptr<Enemy> enemy, CharacterFireball* playerFireball) {
    if (CheckCollisionRecs(playerFireball->getHitBox(), enemy->getHitBox())) {
        enemy->beHitByFireball();
        playerFireball->hitBlockHorizontal();
    }
}