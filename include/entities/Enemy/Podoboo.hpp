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

    bool physics() override;
    void onEnemyCollision(Enemy& enemy) override;
    void update(float dt) override;
};