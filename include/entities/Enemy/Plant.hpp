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
    //Goomba(Vector2 bSpeed, Vector2 pos, Vector2 vel);
    //void init(std::shared_ptr<EnemyType> newType, Vector2 startPosition);
    
    //void draw() override;
    void update(float dt) override;
};