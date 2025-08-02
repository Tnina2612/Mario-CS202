#pragma once

#include<vector>
#include<string>
#include<unordered_map>
#include<memory>
//#include<functional>
#include"raylib.h"

#include"Enemy.hpp"
#include"EnemyType.hpp"

class EnemyFactory {
private:
    static std::shared_ptr<EnemyType> s_enemyTypes;
    static std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Rectangle>>> s_enemyFrames;
public:

    // using EnemyCreator = std::function<std::shared_ptr<Enemy>(const std::string&, Vector2)>;
    // static void registerType(const std::string& prefix, EnemyCreator creator);
    static void loadAllFrames();
    static std::shared_ptr<EnemyType>& getEnemyTypes();
    static std::shared_ptr<Enemy> createEnemy(const std::string& name, Vector2 pos);
};