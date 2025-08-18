#pragma once

#include"Enemy.hpp"
#include"entities/Character.hpp"

class EnemyManager;

class Lakitu : public Enemy {
private:
    EnemyManager* _enemyManager;
    const float _cd = 6.f;
    float spawnTimer = 0.f;
    bool isSpawning = false;
    void spawnSpiny();
public:
    Lakitu();
    Lakitu(const std::string& name);
    Lakitu(const std::string& name, Vector2 pos, EnemyManager* _enemyManager);

    bool physics() override;
    void onEnemyCollision(Enemy& enemy) override;
    bool beHitVertical() override;
    void hitBlockLeft() override;
    void hitBlockRight() override;

    void update(float dt) override;
};