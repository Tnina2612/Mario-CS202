#pragma once

#include"raylib.h"

#include"Enemy.hpp"

class Goomba : public Enemy {
private:
    int _deadAni;   // 0 : not dead, 1 : active, -1 : finished
public:
    float time;
    Goomba();
    Goomba(const std::string& name);
    Goomba(const std::string& name, Vector2 pos);
    //Goomba(Vector2 bSpeed, Vector2 pos, Vector2 vel);
    //void init(std::shared_ptr<EnemyType> newType, Vector2 startPosition);
    bool onHit() override;
    // void draw() override;
    void update(float dt) override;
};