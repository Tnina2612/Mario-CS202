#include<vector>
#include<iostream>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Goomba.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"



Goomba::Goomba() : Enemy() {
    _deadAni = 0;
    m_data._velocity = Vector2{50.f, 0.f};
}

Goomba::Goomba(const std::string& name) : Enemy(name) {
    _deadAni = 0;
    float width = 16.f;
    float height = 16.f;
    m_data = EnemyData (width, height, 1000.f, false, true, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_data._velocity = Vector2{100, 50.f};
    
}

Goomba::Goomba(const std::string& name, Vector2 pos)
    : Goomba(name) {
        m_data._pos = pos;
        //m_data._hitBox = Rectangle{m_data._pos.x, m_data._pos.x, 64, 64};
}

bool Goomba::onHit() {
    if(!Enemy::onHit()) {
        return false;
    }
    if(!isAlive()) {
        /*
        switch deadframes, strategymovement to get out of screen
        setAniFrames(frames["Dead"]);
        setMovementStrategy(...);
        */

        if(_deadAni == 0) {
            setAniFrames(getFrames("Dead"));
            setVelocity(Vector2{20.f, -60.f});
            m_data._dir = 1;
            m_data._isOnGround = false;
            std::cout << "Goomba is dead\n";
            _deadAni = 1;
        }
        if(isOffScreen() == 1 || isOffScreen() == -2) {
            _deadAni = -1;
        }

        if(_deadAni == -1) {
            setActive(false);
        }
        return true;
    }
    return true;
}

void Goomba::onEnemyCollision(Enemy& enemy) {
    changeDirection();
    float overlapX = min(getHitBox().x + getHitBox().width, enemy.getHitBox().x + enemy.getHitBox().width) - max(getHitBox().x, enemy.getHitBox().x);
    if (overlapX <= 0.0f) return;
    
    setPos(Vector2{getPos().x + overlapX * getDirection(), getPos().y});
}

void Goomba::changeDirection() {
    Enemy::changeDirection();
    setAniFrames(getFrames("Walk"));
}