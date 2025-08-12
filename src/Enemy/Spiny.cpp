#include<vector>
#include<iostream>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Spiny.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"



Spiny::Spiny() : Enemy() {
    m_data._velocity = Vector2{0.f, 50.f};
}

Spiny::Spiny(const std::string& name) : Enemy(name) {
    float width = 16.f;
    float height = 16.f;
    m_data = EnemyData (width, height, 1000.f, false, false, false, false, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_data._velocity = Vector2{0, 50.f};
    _state = State::Egg;
}

Spiny::Spiny(const std::string& name, Vector2 pos)
    : Spiny(name) {
        m_data._pos = pos;
        //m_data._hitBox = Rectangle{m_data._pos.x, m_data._pos.x, 64, 64};
}

bool Spiny::physics() {
    return true;
}

// bool Spiny::onHit() {
//     if(!Enemy::onHit()) {
//         return false;
//     }
//     if(!isAlive()) {
//         /*
//         switch deadframes, strategymovement to get out of screen
//         setAniFrames(frames["Dead"]);
//         setMovementStrategy(...);
//         */

//         if(_deadAni == 0) {
//             setAniFrames(getFrames("Dead"));
//             setVelocity(Vector2{20.f, -60.f});
//             m_data._dir = 1;
//             m_data._isOnGround = false;
//             std::cout << "Spiny is dead\n";
//             _deadAni = 1;
//         }
//         if(isOffScreen() == 1 || isOffScreen() == -2) {
//             _deadAni = -1;
//         }

//         if(_deadAni == -1) {
//             setActive(false);
//         }
//         return true;
//     }
//     return true;
// }

bool Spiny::isOnGround() {
    return m_data._isOnGround;
}

void Spiny::onEnemyCollision(Enemy& enemy) {
    changeDirection();
    float overlapX = min(getHitBox().x + getHitBox().width, enemy.getHitBox().x + enemy.getHitBox().width) - max(getHitBox().x, enemy.getHitBox().x);
    if (overlapX <= 0.0f) return;
    
    setPos(Vector2{getPos().x + overlapX * getDirection(), getPos().y});
}

void Spiny::changeDirection() {
    Enemy::changeDirection();
    if(m_data._dir == 1) {
        m_animation.setFrames(getFrames("Right"));
    } else if(m_data._dir == -1) {
        m_animation.setFrames(getFrames("Left"));
    }
}

void Spiny::hitBlockLeft() {
    Enemy::hitBlockLeft();
    m_animation.setFrames(getFrames("Left"));
}

void Spiny::hitBlockRight() {
    Enemy::hitBlockRight();
    m_animation.setFrames(getFrames("Right"));
}

void Spiny::update(float dt) {
    Enemy::update(dt);
    if (_state == State::Egg) {
        if (isOnGround()) {
            _state = State::Walking;
            setAniFrames(getFrames("Walk"));
            m_data._velocity = Vector2{100.f, 0.f};
            _state = State::Walking;

            if(m_data._dir == 1) {
                m_animation.setFrames(getFrames("Right"));
            } 
            else if(m_data._dir == -1) {
                m_animation.setFrames(getFrames("Left"));
            }
        }
    }
}