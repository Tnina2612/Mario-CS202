#pragma once

#include"IEnemyStrategy.hpp"


class DirectionMove : public IEnemyStrategy {
public:
    void Execute(Enemy& enemy, float dt, Vector2 direction) override;
};

class JumpMove : public IEnemyStrategy {
public:
    void Execute(Enemy& enemy, float dt, Vector2 direction) override;
};




