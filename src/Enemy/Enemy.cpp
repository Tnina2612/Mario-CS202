#include<memory>
#include<string>
#include<iostream>
#include<unordered_map>
#include"raylib.h"

#include"../../include/entities/Enemy/Enemy.hpp"
#include"../../include/entities/Enemy/EnemyType.hpp"

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
    m_animation.sprite = m_data._type->sprite;
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
                        m_data._pos.y, 
                        m_data._hitBoxWidth,
                        m_data._hitBoxHeight   
                    };
}

bool Enemy::isAlive() {
    return m_data._hp > 0;
}

// void Enemy::changeDirection() {
//     m_data._velocity = {m_data._velocity.x*-1, m_data._velocity.y*-1};

//     //setMovementStrategy(_movementStrategy)

// }

int Enemy::isOffScreen() {
    return 2;
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


void Enemy::draw() {
    if(!m_data._isActive) {
        return;
    }

    DrawRectangleRec(getHitBox(), BLUE);
    m_animation.draw(m_data._pos);
    
}

void Enemy::update(float dt) {
    if(!m_data._isActive) {
        return;
    }

    //m_data._velocity.y += m_data._gravity;
    // if() {

    // }
    m_animation.update(dt);
    if(_movementStrategy) {
        _movementStrategy->Execute(m_data, dt);
    }
}
void Enemy::changeDirection() {
    m_data._dir *= -1; 
    m_data._velocity.x *= -1;
    m_data._velocity.y *= -1;

    if(m_data._dir == 1) {
        setAniFrames(getFrames("RWalk"));
    }
    else if(m_data._dir == -1) {
        setAniFrames(getFrames("LWalk"));
    }
}

void Enemy::hitEnemy() {
    this->changeDirection();
}

void Enemy::hitUp() {
    onStomp();
}

void Enemy::hitDown() {
    onStomp();
}

void Enemy::hitLeft() {
    return;
}

void Enemy::hitRight() {
    return;
}