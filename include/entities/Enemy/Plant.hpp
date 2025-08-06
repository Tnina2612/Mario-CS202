#pragma once

#include"raylib.h"

#include"Enemy.hpp"

class Plant : public Enemy {
private:
    float _curCD;             //
    float _cdTime = 1.f;            //
    bool _inCD;             //
    int _curDir;    // -1 : up, 1 : down
    float _curHeight;
    float _maxHeight;
public:
    Plant();
    Plant(const std::string& name);
    Plant(const std::string& name, Vector2 pos);
    
    void onEnemyCollision(Enemy& enemy) override;
    void update(float dt) override;
};