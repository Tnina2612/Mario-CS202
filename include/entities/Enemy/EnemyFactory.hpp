#pragma once

#include<memory>
#include<string>
#include<unordered_map>

#include"EnemyType.hpp"
#include"EnemyMove.hpp"

class EnemyFactory {
public:
    static std::shared_ptr<EnemyType> getEnemy(const std::string& name);
private:
    static std::unordered_map<std::string, std::shared_ptr<EnemyType>> s_enemies;
    static std::shared_ptr<DirectionMove> directionMove;
    static std::shared_ptr<JumpMove> jumpMove;

    static void init();
};