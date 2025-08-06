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
    for(auto& enemy : list) {
        enemy->update();
        subLevel->blocks->update(enemy);
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
            if(enemy->getTypeName() == type) {
                count++;
            }
        }
        out << count << " " << type << endl;
        for(const auto& enemy : list) {
            if(enemy->getTypeName() == type) {
                Vector2 pos = enemy->getPos();
                out << pos.x << " " << pos.y << endl;
            }
        }
    }
    out.close();
}