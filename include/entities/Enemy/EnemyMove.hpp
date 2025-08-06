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

class PatrolMove : public IEnemyStrategy {
public:
    Vector2 Execute(EnemyData& data, float dt) override;
};

class AngularMove : public IEnemyStrategy {
private:
    float _angle;
    float _rotationSpeed;
    float _radius;
    Vector2 _center;
public:
    AngularMove(Vector2 center, float angle = 0.f, float radius = 50.f, float speed = 2.f)
        : _center(center), _angle(angle), _radius(radius), _rotationSpeed(speed) {}

    Vector2 Execute(EnemyData& data, float dt) override;
};



