#pragma once

#include"IEnemyStrategy.hpp"


class DirectionMove : public IEnemyStrategy {
private:
    Vector2 direction;
public:
    DirectionMove(Vector2 dir) : direction(dir) {}
    void Execute(Enemy& enemy, float dt) override;
};

class JumpMove : public IEnemyStrategy {
public:
    void Execute(Enemy& enemy, float dt) override;
};




