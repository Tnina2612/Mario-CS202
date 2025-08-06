#pragma once

#include"EnemyData.hpp"

class IEnemyStrategy {
public:
    virtual ~IEnemyStrategy() = default;
    virtual Vector2 Execute(EnemyData& data, float dt) = 0;
};