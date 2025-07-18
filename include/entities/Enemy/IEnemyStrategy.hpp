#pragma once

#include"raylib.h"

class Enemy;

class IEnemyStrategy {
public:
    virtual ~IEnemyStrategy() = default;
    virtual void Execute(Enemy& enemy, float dt, Vector2 direction) = 0;
};