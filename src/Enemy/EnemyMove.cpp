#include"raylib.h"
#include<cmath>

#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include<iostream>
//Movement
Vector2 DirectionMove::Execute(EnemyData& data, float dt) {
    Vector2 res = {0.f, 0.f};
    res.x = data._velocity.x * data._dir * dt;
    res.y = data._velocity.y * data._dir * dt;
    return res;
}

Vector2 JumpMove::Execute(EnemyData& data, float dt) {
    Vector2 res = {0.f, 0.f};
    data._velocity.y += data._gravity * dt;

    res.x = data._velocity.x * dt;
    res.y = data._velocity.y * dt;

    if(data._isOnGround) {
        //data._pos.y = ;
    }
    return res;
}

Vector2 PatrolMove::Execute(EnemyData& data, float dt) {
    Vector2 res = {0.f, 0.f};
    // Implement patrol movement logic
    return res;
}

Vector2 AngularMove::Execute(EnemyData& data, float dt) {
    _angle += _rotationSpeed * dt;
    data._pos.x = _center.x + _radius * cosf(_angle);
    data._pos.y = _center.y + _radius * sinf(_angle);
    return data._pos;
}