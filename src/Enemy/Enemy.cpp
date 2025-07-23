#include<memory>
#include<string>

#include"raylib.h"

#include"../../include/entities/Enemy/Enemy.hpp"
#include"../../include/entities/Enemy/EnemyType.hpp"


std::shared_ptr<EnemyType> Enemy::getEnemyType() {
    return m_data._type;
}

Vector2 Enemy::getBaseSpeed() {
    return m_data._baseSpeed;
}

void Enemy::setActive(bool isActive) {
    m_data._isActive = isActive;
}

bool Enemy::isAlive() {
    return m_data._hp > 0 || !m_data._isActive;
}

bool Enemy::onHit() {
    setActive(false);
    return true;
}

bool Enemy::onStomp() {
    if(!m_data._isActive) {
        return false;
    }

    if(!m_data._isStompable) {
        return false;
    }
    m_data._hp--;
    if(!isAlive()) {
        onStomp();
    }
    return true;
}

bool Enemy::beHitByFireball() {
    if(!m_data._isActive) {
        return false;
    }

    if(!m_data._isImuneFire) {
        return false;
    }

    m_data._hp--;
    if(!isAlive()) {
        onHit();
    }
    return true;
}

void Enemy::setVelocity(Vector2 vel) {
    m_data._velocity = vel;
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
    m_data._type->draw(m_data._pos);
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