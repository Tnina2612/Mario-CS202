#pragma once

#include"IEnemyStrategy.hpp"


class DirectionMove : public IEnemyStrategy {
private:
    //float length; 
public:
    // DirectionMove(float len)
    //     : length(len) {}
    void Execute(Enemy& enemy, float dt, Vector2 direction) override;
};

class JumpMove : public IEnemyStrategy {
private:
    float height;
    float gravity;
public:
    JumpMove(float h, float g) 
        : height(h), gravity(g) {}
    void Execute(Enemy& enemy, float dt, Vector2 direction) override;
};




