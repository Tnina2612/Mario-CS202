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

void Enemy::setFrames(const std::vector<Rectangle>& frames) {
    m_animation.setFrames(frames);
}

void Enemy::setType(std::shared_ptr<EnemyType> type) {
    m_data._type = type;
    m_animation.sprite = m_data._type->sprite;
}

void Enemy::setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy) {
    m_data._movementStrategy = strategy;
}

void Enemy::setEnemyData(const EnemyData& data) {
    m_data = data;
}

void Enemy::setDirection(int dir) {
    m_data._dir = dir;
}

int Enemy::getDirection() {
    return m_data._dir;
}

Vector2 Enemy::getVelocity() {
    return m_data._velocity;
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


void Enemy::draw() {
    if(!m_data._isActive || !isAlive()) {
        return;
    }

    m_animation.draw(m_data._pos);
}

void Enemy::update(float dt) {
    if(!m_data._isActive) {
        return;
    }

    m_data._velocity.y += m_data._gravity;
    // if() {

    // }
    m_animation.update(dt);
    if(m_data._movementStrategy) {
        m_data._movementStrategy->Execute(m_data._pos, dt);
    }
}