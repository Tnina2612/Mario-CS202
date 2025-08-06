#pragma once

#include"Enemy.hpp"

class Podoboo : public Enemy {
private:
    float _curCD;
    float _CD;
public:
    Podoboo();
    Podoboo(const std::string& name);
    Podoboo(const std::string& name, Vector2 pos);

    void onEnemyCollision(Enemy& enemy) override;
    void update(float dt) override;
};