#include"raylib.h"
#include<cmath>

#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include<iostream>
//Movement
Vector2 DirectionMove::Execute(EnemyData& data, float dt) {
    Vector2 res = {0.f, 0.f};
    res.x = data._velocity.x * data._dir * dt;
    res.y = data._velocity.y * dt;
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

Vector2 LakituMove::Execute(EnemyData& data, float dt) {
    Vector2 res = {0.f, 0.f};

    if(yBase == 0.f) {
        yBase = data._pos.y;
    }

    Vector2 playerPos = data._targetPos;
    if (playerPos.x > data._pos.x) {
        res.x = data._velocity.x * dt;
    } 
    else if (playerPos.x < data._pos.x) {
        res.x = -data._velocity.x * dt;
    } 
    else {
        res.x = 0.f;
    }

    if (movingUp) {
        res.y = -floatSpeed * dt;
        if (res.y <= 20.f) {
            movingUp = false;
        }
    } else {
        res.y = floatSpeed * dt;
        if (res.y >= 20.f) {
            movingUp = true;
        }
    }

    return res;
}

// Vector2 PlantMove::Execute(EnemyData& data, float dt) {
//     Vector2 res = {data._velocity.x * dt, data._velocity.y * dt};
//     return res;
// }