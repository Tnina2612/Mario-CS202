#pragma once

#include"raylib.h"

#include"Enemy.hpp"

class EnemyManager;

class Plant : public Enemy {
public:
    Plant();
    Plant(const std::string& name);
    Plant(const std::string& name, Vector2 pos);
    
    bool physics() override;
    bool onHit() override;
    void onEnemyCollision(Enemy& enemy) override;
    bool beHitVertical() override;
    void update(float dt) override;
};