#pragma once

#include<vector>
#include<string>
#include<unordered_map>
#include<memory>
#include"raylib.h"

#include"Enemy.hpp"
#include"EnemyType.hpp"

class EnemyManager;

class EnemyFactory {
private:
    static std::shared_ptr<EnemyType> s_enemyTypes;
    static std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Rectangle>>> s_enemyFrames;
public:
    static void loadAllFrames();
    static std::shared_ptr<EnemyType>& getEnemyTypes();
    static std::shared_ptr<Enemy> createEnemy(const std::string& name, Vector2 pos, EnemyManager* enemyManager);
    static std::vector<std::string> getEnemyTypesNames();
};