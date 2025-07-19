#include"raylib.h"

#include"../include/entities/Enemy/Enemy.hpp"
#include"../include/entities/Enemy/EnemyType.hpp"

void Enemy::init(EnemyType* newType, Vector2 startPos) {
    this->_type = newType;
    this->_pos = startPos;
    
    this->_isOnGround = true;
    this->_isActive = false;
}

void Enemy::draw() {
    if(!_isActive) {
        return;
    }
    _type->draw();
}

void Enemy::update(float dt) {
    if(!_isActive) {
        return;
    }

    _velocity.y += _type->getGravity();

    if(_type->getMovementStrategy()) {
        Vector2 dir = {-1,0};
        _type->getMovementStrategy()->Execute(*this, dt, dir);
    }

}