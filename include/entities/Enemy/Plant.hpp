#pragma once

#include"raylib.h"

#include"Enemy.hpp"

class EnemyManager;

class Plant : public Enemy {
private:
    // float _curCD;             //
    // float _cdTime = 1.f;            //
    // bool _inCD;             //
    // int _curDir;    // -1 : up, 1 : down
    // float _curHeight;
    // float _maxHeight;

    // EnemyManager* _enemyManager;
    // enum State {

    // } _state;
public:
    Plant();
    Plant(const std::string& name);
    Plant(const std::string& name, Vector2 pos);
    
    bool physics() override;
    bool onHit() override;
    void onEnemyCollision(Enemy& enemy) override;
    void update(float dt) override;
};