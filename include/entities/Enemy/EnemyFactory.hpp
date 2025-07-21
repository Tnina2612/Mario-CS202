#pragma once

#include<memory>
#include<string>
#include<unordered_map>

#include"EnemyType.hpp"
#include"EnemyMove.hpp"

class EnemyFactory {
private:
    static std::unordered_map<std::string, std::shared_ptr<EnemyType>> s_enemyTypes;
    static std::shared_ptr<DirectionMove> s_directionMove;
    static std::shared_ptr<JumpMove> s_jumpMove;

    //ObjectPool<Enemy> ....
public:
    static std::shared_ptr<EnemyType> getEnemyType(const std::string& name);
    static std::shared_ptr<DirectionMove> getDirectionMove();
    static std::shared_ptr<JumpMove> getJumpMove();
    
    //void loadEnemyTypes();
    //void releaseEnemy();          //< object pool


};