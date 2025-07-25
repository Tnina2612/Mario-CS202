#pragma once

#include"raylib.h"

class IEnemyStrategy {
public:
    virtual ~IEnemyStrategy() = default;
    virtual void Execute(Vector2& position, float dt) = 0;
};