#pragma once

#include<memory>
#include"raylib.h"
#include<string>

#include"EnemyType.hpp"


struct EnemyData {
    std::shared_ptr<EnemyType> _type;
    std::shared_ptr<IEnemyStrategy> _movementStrategy;
    std::string _name;  //< Enemy name 

    Rectangle _hitBox;

    int _hp;

    //Vector2 _baseSpeed;
    Vector2 _pos;
    Vector2 _velocity;

    float _gravity;

    bool _isImuneFire;
    bool _isStompable;
    bool _isActive;
    bool _isOnGround;

    int _dir;   // Direction: 1 facing right, -1 left
                // -1 : up, 1 : down

    EnemyData(
        //std::string name,
        //std::shared_ptr<EnemyType> type,
        Rectangle hitBox,
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
        _hitBox(hitBox),
        //_baseSpeed(baseSpeed),
        _pos(pos),
        _velocity(vel),
        _gravity(gra),
        _isImuneFire(imuneFire),
        _isStompable(isStompable),
        _isOnGround(isOnGround),
        //_type(type),
        _hp(hp),
        //_isActive(false),
        _dir(dir)
    {}

    EnemyData(): _isActive(false), _type(), _movementStrategy(nullptr) {}
    EnemyData(
        Rectangle hitBox,
        float gra,
        bool imuneFire,
        bool isStompable,
        bool isOnGround,
        int hp,

        //Vector2 baseSpeed,
        Vector2 vel,
        
        int dir

    ):  _type(),
        _hitBox(hitBox),
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
};