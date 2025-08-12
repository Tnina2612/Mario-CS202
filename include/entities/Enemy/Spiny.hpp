#pragma once

#include"Enemy.hpp"

class Spiny : public Enemy {
private:
    bool _isSpawing = true;
    enum State {
        Egg,
        Walking
    } _state;

    bool isOnGround();
public:
    Spiny();
    Spiny(const std::string& name);
    Spiny(const std::string& name, Vector2 pos);

    void hitBlockLeft() override;
    void hitBlockRight() override;
    
    bool physics() override;
    void changeDirection() override;
    void onEnemyCollision(Enemy& enemy) override;
    void update(float dt) override;
};