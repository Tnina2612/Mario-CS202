#pragma once

#include"raylib.h"

#include"IEnemyStrategy.hpp"


class DirectionMove : public IEnemyStrategy {
private:
    Vector2 direction;
public:
    DirectionMove() : direction(Vector2{1.f, 0.f}) {}
    DirectionMove(Vector2 dir) : direction(dir) {}
    void Execute(Enemy& enemy, float dt) override;
};

class JumpMove : public IEnemyStrategy {
public:
    void Execute(Enemy& enemy, float dt) override;
};




