#pragma once

#include<memory>
#include<string>
#include<unordered_map>

#include"EnemyType.hpp"
#include"EnemyMove.hpp"

class EnemyFactory {
private:
    std::unordered_map<std::string, std::shared_ptr<EnemyType>> enemyTypes;
    std::shared_ptr<DirectionMove> directionMove;
    std::shared_ptr<JumpMove> jumpMove;

    //ObjectPool<Enemy> ....

public:
    //EnemyFactory();
    std::shared_ptr<EnemyType> getEnemyType(const std::string& name);
    //void loadEnemyTypes();
    //void releaseEnemy();          //< object pool


};