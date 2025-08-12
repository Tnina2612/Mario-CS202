#include<memory>
#include<string>
#include<iostream>
#include<unordered_map>
#include"raylib.h"

#include"../../include/entities/Enemy/Enemy.hpp"
#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/core/Variables.hpp"

#include<iostream>
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

void Enemy::setAllFrames(std::unordered_map<std::string, std::vector<Rectangle>> frames) {
    allFrames = frames;
}
void Enemy::setAniFrames(const std::vector<Rectangle>& frames) {
    m_animation.setFrames(frames);
}

void Enemy::setType(std::shared_ptr<EnemyType> type) {
    m_data._type = type;
    m_animation.setSprite(m_data._type->sprite);
}

void Enemy::setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy) {
    _movementStrategy = strategy;
}

void Enemy::setEnemyData(const EnemyData& data) {
    m_data = data;
}

void Enemy::setDirection(int dir) {
    m_data._dir = dir;
}

void Enemy::setOnGround(bool onGround) {
    m_data._isOnGround = onGround;
}

void Enemy::setVelocity(Vector2 d) {
    m_data._velocity = d;
}

int Enemy::getDirection() {
    return m_data._dir;
}

Vector2 Enemy::getVelocity() {
    return m_data._velocity;
}

Vector2 Enemy::getPos() {
    return m_data._pos;
}

std::vector<Rectangle> Enemy::getFrames(const std::string& name) {
    return allFrames[name];
}

std::shared_ptr<IEnemyStrategy> Enemy::getMovementStrategy() {
    return _movementStrategy;
}

EnemyData& Enemy::getEnemyData() {
    return m_data;
}

void Enemy::setVelocityX(float x) {
    m_data._velocity.x = x;
}

void Enemy::setVelocityY(float y) {
    m_data._velocity.y = y;
}

void Enemy::setPos(Vector2 pos) {
    m_data._pos = pos;
}

Rectangle Enemy::getHitBox() {
    return Rectangle{   m_data._pos.x, 
                        m_data._pos.y - m_data._hitBoxHeight, 
                        m_data._hitBoxWidth,
                        m_data._hitBoxHeight   
                    };
}

bool Enemy::isAlive() {
    return m_data._hp > 0;
}

int Enemy::isOffScreen() {
    if(m_data._pos.y > Global::ORIGINAL_HEIGHT) {
        return 1;
    }
    else if(m_data._pos.y <= 0) {
        return -1;
    }
    else if(m_data._pos.x > Global::ORIGINAL_WIDTH) {
        return 2;
    }
    else if(m_data._pos.x <= 0) {
        return -2;
    }
    return 0;
}

bool Enemy::onHit() {
    if(!m_data._isActive) {
        return false;
    }
    m_data._hp--;
    return true;
}

bool Enemy::onStomp() {
    if(!m_data._isActive) {
        return false;
    }

    if(!m_data._isStompable) {
        return false;
    }
    onHit();
    return true;
}

bool Enemy::beHitByFireball() {
    if(!m_data._isActive) {
        return false;
    }

    if(!m_data._isImuneFire) {
        return false;
    }

    onHit();
    return true;
}

float Enemy::getGravity() {
    return m_data._gravity;
}

bool Enemy::getOnGround() {
    return m_data._isOnGround;
}

void Enemy::applyGravity(float dt) {
    if(!m_data._isOnGround) {
        m_data._velocity.y += m_data._gravity * dt;
    }
}

void Enemy::draw() {
    if(!m_data._isActive) {
        return;
    }

    DrawRectangleRec(getHitBox(), BLUE);
    m_animation.draw({m_data._pos.x, m_data._pos.y - m_data._hitBoxHeight});
}

void Enemy::update(float dt) {
    if(!m_data._isActive) {
        return;
    }
    m_animation.update(dt);
}

std::string Enemy::getTypeName() const {
    return m_data.getTypeName();
}

void Enemy::changeDirection() {
    m_data._dir *= -1; 
}

void Enemy::hitUp() {
    onStomp();
}

void Enemy::hitBlockDown() {
    onStomp();
}

void Enemy::hitBlockLeft() {
    m_data._dir = -1;
}

void Enemy::hitBlockRight() {
    m_data._dir = 1;
}

float Enemy::getRestVelocity()const {
    return m_data._restVelocityY;
}