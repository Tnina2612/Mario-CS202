#include"raylib.h"
#include<cmath>

#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/level/Level.hpp"
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

    if(data._isOnGround) {
        data._velocity.y = -200.0f;
        data._isOnGround = false;
    }

    res.x = data._velocity.x * data._dir * dt;
    res.y = data._velocity.y * dt;

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

    // if (movingUp) {
    //     res.y = -floatSpeed * dt;
    //     if (data._pos.y - yBase >= 20.f) {
    //         movingUp = false;
    //     }
    // } else {
    //     res.y = floatSpeed * dt;
    //     if (data._pos.y - yBase <= 20.f) {
    //         movingUp = true;
    //     }
    // }

    return res;
}

PlantMove::PlantMove(EnemyManager* manager) {
    _manager = manager;
}

Vector2 PlantMove::Execute(EnemyData& data, float dt) {
    if(_curDir == 0) {
        _pos = data._pos;
        _curDir = -1;
    }

    if (!_manager) {
        return {0.f, 0.f};
    }
    
    if (_inCD) {
        _curCD += dt;
        if (_curCD > _cdTime) {
            _inCD = false;
            _curCD = 0.f;
        }
        return {0.f, 0.f};
    }

    Vector2 pos = _manager->getPlayerPos();
    float dis = pos.y - data._pos.y;

    bool nearHoriz = std::fabs(pos.x - data._pos.x) < 28.f;
    bool abovePipe = (pos.y + 24.f) <= _pos.y;

    bool shouldMove = !(nearHoriz && abovePipe);

    if (!shouldMove) {
        _curCD = 0.f;
        _inCD = true;
        return {0.f, 0.f};
    }

    float dy = data._velocity.y * dt * _curDir;
    _curHeight += dy;

    if (_curHeight + _maxHeight <= 0.f) {
        _curHeight = -1*_maxHeight;
        _curDir = 1;
        _cdTime = 0.1f;
        _inCD = true;
    }
    else if (_curHeight >= _maxHeight) {
        _curHeight = _maxHeight;
        _curDir = -1;
        _cdTime = 2.f;
        _inCD = true;
    }

    return {0.f, dy};
}