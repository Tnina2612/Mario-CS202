#include<memory>
#include<string>
#include<iostream>
#include"raylib.h"

#include"../../include/entities/Enemy/Enemy.hpp"
#include"../../include/entities/Enemy/EnemyType.hpp"


Enemy::Enemy() : m_data() {}

Enemy::Enemy(const std::string& name)  
    : Enemy() 
{
    m_data._name = name;
}

Enemy::Enemy(const std::string& name, Vector2 pos) 
    : Enemy(name) 
{
    m_data._pos = pos;
}

void Enemy::setActive(bool isActive) {
    m_data._isActive = isActive;
}

void Enemy::setFrames(std::vector<Rectangle> frames) {
    if(!m_data._type) {
        std::cerr << "E1" << std::endl;
        return;
    }
    m_data._type->setFrames(frames);
}

void Enemy::setType(std::shared_ptr<EnemyType> type) {
    m_data._type = type;
}

void Enemy::setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy) {
    if(m_data._type)
        m_data._type->setMovementStrategy(strategy);
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

// void Enemy::init(std::shared_ptr<EnemyType> newType, Vector2 startPos) {
//     this->m_data._type = newType;
//     this->m_data._pos = startPos;
    
//     this->m_data._isOnGround = true;
//     this->m_data._isActive = false;
// }

void Enemy::draw() {
    if(!m_data._isActive) {
        return;
    }
    std::cerr << "OKE3" << std::endl;
    m_data._type->draw(m_data._pos);
}

void Enemy::update(float dt) {
    if(!m_data._isActive) {
        return;
    }

    m_data._velocity.y += m_data._gravity;
    // if() {

    // }
    m_data._type->update(dt, m_data._pos);
}