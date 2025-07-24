#pragma once

#include"raylib.h"

#include"IEnemyStrategy.hpp"


class DirectionMove : public IEnemyStrategy {
private:
    Vector2 velocity;
public:
    DirectionMove(Vector2 vel = {-100.f, 0.f}) 
        : velocity(vel) {}
    void Execute(Vector2& position, float dt) override;
};

class JumpMove : public IEnemyStrategy {
private:
    float jumpHeight;
    float gravity;
    Vector2 velocity;
public:
    JumpMove(float h = 300.f, float g = 800.f)
        : jumpHeight(h), gravity(g), velocity(Vector2{-100.f,100.f}) {}
    void Execute(Vector2& position, float dt) override;
};




