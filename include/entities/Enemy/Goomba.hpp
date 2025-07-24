#pragma once

#include"raylib.h"

#include"Enemy.hpp"

class Goomba : public Enemy {
public:
    Goomba();
    Goomba(const std::string& name);
    Goomba(const std::string& name, Vector2 pos);
    //Goomba(Vector2 bSpeed, Vector2 pos, Vector2 vel);
    //void init(std::shared_ptr<EnemyType> newType, Vector2 startPosition);
    
    // void draw() override;
    // void update(float dt) override;
};