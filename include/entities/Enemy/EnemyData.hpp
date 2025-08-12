#pragma once

#include<memory>
#include"raylib.h"
#include<string>

#include"EnemyType.hpp"


struct EnemyData {
    std::shared_ptr<EnemyType> _type;
    std::string _name;  //< Enemy name 

    float _hitBoxHeight;
    float _hitBoxWidth;
    int _hp;

    Vector2 _pos;
    Vector2 _velocity;
    Vector2 _targetPos = Vector2{0.f, 0.f};

    float _gravity;
    bool _preventFalling;
    bool _isImuneFire;
    bool _isStompable;
    bool _isActive;
    bool _isOnGround;

    float _restVelocityY = 50.0f;

    int _dir;   // Direction: 1 facing right, -1 left
                // -1 : up, 1 : down
                //  0 : stationary
    int _dirY = 1;
    EnemyData(
        float width,
        float height,
        float gra,
        bool imuneFire,
        bool isStompable,
        bool isOnGround,
        bool preventFall,
        int hp,
        Vector2 pos,
        Vector2 vel,
        int dir
    ):  _type(),
        _hitBoxWidth(width),
        _hitBoxHeight(height),
        _pos(pos),
        _velocity(vel),
        _gravity(gra),
        _preventFalling(preventFall),
        _isImuneFire(imuneFire),
        _isStompable(isStompable),
        _isOnGround(isOnGround),
        _hp(hp),
        _dir(dir)
    {}

    EnemyData(): _isActive(false), _type() {}
    
    std::string getTypeName() const {
        return _name;
    }
};