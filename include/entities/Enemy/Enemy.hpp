#pragma once

#include<memory>
#include"raylib.h"

#include"EnemyType.hpp"
#include"IEnemyStrategy.hpp"

class Enemy {
private:
    std::shared_ptr<EnemyType> _type;
    
    Vector2 _pos;
    Vector2 _velocity;

    //int _direction; // 1 right, -1 left
    bool _isActive;
    bool _isOnGround;

    int _curHp;
public:
    //Enemy();
    Enemy(std::shared_ptr<EnemyType> type)
        : _type(type) {}
    Enemy(std::shared_ptr<EnemyType> type, Vector2 pos)
        : _type(type), _pos(pos) {}
    void init(EnemyType* newType, Vector2 startPosition);
    void draw(); 
    void update(float dt);
};