#pragma once

#include<memory>
#include"raylib.h"
#include<string>

#include"EnemyType.hpp"


struct EnemyData {
    std::shared_ptr<EnemyType> _type;
    std::string _name;  //< Enemy name 

    //Rectangle _hitBox;

    float _hitBoxHeight;
    float _hitBoxWidth;
    int _hp;

    //Vector2 _baseSpeed;
    Vector2 _pos;
    Vector2 _velocity;

    float _gravity;

    bool _isImuneFire;
    bool _isStompable;
    bool _isActive;
    bool _isOnGround;

    float _restVelocityY = 50.0f;

    int _dir;   // Direction: 1 facing right, -1 left
                // -1 : up, 1 : down
                //  0 : stationary

    EnemyData(
        //std::string name,
        //std::shared_ptr<EnemyType> type,
        float width,
        float height,
        float gra,
        bool imuneFire,
        bool isStompable,
        bool isOnGround,
        int hp,

        //Vector2 baseSpeed,
        Vector2 pos,
        Vector2 vel,

        int dir

    ):  //_name(name),
        _type(),
        _hitBoxWidth(width),
        _hitBoxHeight(height),
        //_baseSpeed(baseSpeed),
        _pos(pos),
        _velocity(vel),
        _gravity(gra),
        _isImuneFire(imuneFire),
        _isStompable(isStompable),
        _isOnGround(isOnGround),
        _hp(hp),
        //_isActive(false),
        _dir(dir)
    {}

    EnemyData(): _isActive(false), _type() {}
    EnemyData(
        float width,
        float height,
        float gra,
        bool imuneFire,
        bool isStompable,
        bool isOnGround,
        int hp,

        //Vector2 baseSpeed,
        Vector2 vel,
        
        int dir

    ):  _type(),
        _hitBoxWidth(width),
        _hitBoxHeight(height),
        //_baseSpeed(baseSpeed),
        _velocity(vel),
        _gravity(gra),
        _isImuneFire(imuneFire),
        _isStompable(isStompable),
        _isOnGround(isOnGround),
        _hp(hp),
        _dir(dir)
    {}
    EnemyData(std::shared_ptr<EnemyType> type)
        : _type(type){}
    
    std::string getTypeName() const {
        return _name;
    }
};