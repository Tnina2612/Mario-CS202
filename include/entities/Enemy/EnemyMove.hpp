#pragma once

#include"IEnemyStrategy.hpp"
#include"EnemyData.hpp"

class DirectionMove : public IEnemyStrategy {
public:
    Vector2 Execute(EnemyData& data, float dt) override;
};

class JumpMove : public IEnemyStrategy {
public:
    Vector2 Execute(EnemyData& data, float dt) override;
};

class LakituMove : public IEnemyStrategy {
private:
    float floatAmplitude = 10.f;
    float floatSpeed = 2.f;
    float yBase = 0.f;
    bool movingUp = true;
public:
    Vector2 Execute(EnemyData& data, float dt) override;
};

// class PlantMove : public IEnemyStrategy {
// public:
//     Vector2 Execute(EnemyData& data, float dt) override;
// };