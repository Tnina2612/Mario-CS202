#pragma once

#include"IEnemyStrategy.hpp"
#include"EnemyData.hpp"

class DirectionMove : public IEnemyStrategy {
public:
    void Execute(EnemyData& data, float dt) override;
};

class JumpMove : public IEnemyStrategy {
public:
    void Execute(EnemyData& data, float dt) override;
};

class PatrolMove : public IEnemyStrategy {
public:
    void Execute(EnemyData& data, float dt) override;
};



