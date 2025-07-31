#pragma once

#include"EnemyData.hpp"

class IEnemyStrategy {
public:
    virtual ~IEnemyStrategy() = default;
    virtual void Execute(EnemyData& data, float dt) = 0;
};