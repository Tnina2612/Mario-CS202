#pragma once

#include"IEnemyStrategy.hpp"
#include"EnemyData.hpp"

class EnemyManager;

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

class PlantMove : public IEnemyStrategy {
private:
    float _curCD = 0.f;            // Current cooldown
    float _cdTime = 2.f;           // Cooldown time
    bool _inCD = true;             // Is in cooldown
    int _curDir = 0;               // -1 : up, 1 : down
    bool spawning = false;
    float _curHeight = 12.f;
    float _maxHeight = 12.f;
    Vector2 _pos = Vector2{0.f, 0.f};
    EnemyManager* _manager;
public:
    PlantMove(EnemyManager* manager);
    Vector2 Execute(EnemyData& data, float dt) override;
};