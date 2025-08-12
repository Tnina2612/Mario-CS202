#pragma once

#include"raylib.h"

#include"Enemy.hpp"

class Goomba : public Enemy {
private:
    int _deadAni;   // 0 : not dead, 1 : active, -1 : finished
public:
    Goomba();
    Goomba(const std::string& name);
    Goomba(const std::string& name, Vector2 pos);

    bool physics() override;
    void changeDirection() override;
    bool onHit() override;
    void onEnemyCollision(Enemy& enemy) override;
};