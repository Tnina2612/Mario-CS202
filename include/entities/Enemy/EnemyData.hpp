#pragma once

#include<memory>
#include"raylib.h"
#include<string>

#include"EnemyType.hpp"

struct EnemyData {
    std::shared_ptr<EnemyType> _type;

    std::string _name;  //< Enemy name 
    Rectangle _hitBox;

    int _hp;

    Vector2 _baseSpeed;
    Vector2 _pos;
    Vector2 _velocity;

    float _gravity;

    bool _isImuneFire;
    bool _isStompable;
    bool _isActive;
    bool _isOnGround;

    EnemyData(
        std::string name,
        Texture2D tex,
        Rectangle hitBox,
        std::shared_ptr<IEnemyStrategy> move, 
        Vector2 baseSpeed,
        Vector2 pos,
        Vector2 vel,
        float gra,
        bool imuneFire,
        bool isStompable,
        int hp
    ):  _name(name),
        //_sprite(tex),
        _hitBox(hitBox),
        //_movementStrategy(move),
        _baseSpeed(baseSpeed),
        _pos(pos),
        _velocity(vel),
        _gravity(gra),
        _isImuneFire(imuneFire),
        _isStompable(isStompable),
        _type(&EnemyType(tex, move)),
        _hp(hp),
        _isActive(false)
    {}
};