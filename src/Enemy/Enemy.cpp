#include<memory>
#include<string>

#include"raylib.h"

#include"../include/entities/Enemy/Enemy.hpp"
#include"../include/entities/Enemy/EnemyType.hpp"


std::shared_ptr<EnemyType> Enemy::getEnemyType() {
    return m_data._type;
}

Vector2 Enemy::getBaseSpeed() {
    return m_data._baseSpeed;
}

void Enemy::init(std::shared_ptr<EnemyType> newType, Vector2 startPos) {
    this->m_data._type = newType;
    this->m_data._pos = startPos;
    
    this->m_data._isOnGround = true;
    this->m_data._isActive = false;
}

void Enemy::draw() {
    if(!m_data._isActive) {
        return;
    }
    m_data._type->draw();
}

void Enemy::update(float dt) {
    if(!m_data._isActive) {
        return;
    }

    m_data._velocity.y += m_data._gravity;

    if(m_data._type->getMovementStrategy()) {
        //Vector2 dir = {-1,0};
        m_data._type->getMovementStrategy()->Execute(*this, dt);
    }

}