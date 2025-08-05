#include<vector>
#include<iostream>
#include<cmath>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Podoboo.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"



Podoboo::Podoboo() : Enemy() {
    m_data._velocity = Vector2{0.f, -100.f};
    _curCD = 0.f;
    _CD = 3.f;
}

Podoboo::Podoboo(const std::string& name) : Enemy(name) {
    float width = 16.f;
    float height = 16.f;
    m_data = EnemyData (width, height, 20, true, false, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_data._velocity = Vector2{0.f, -100.f};
    _curCD = 0.f;
    _CD = 3.f;
    
}

Podoboo::Podoboo(const std::string& name, Vector2 pos)
    : Podoboo(name) {
        m_data._pos = pos;
}

void Podoboo::update(float dt) {
    _curCD += dt;
    if(_curCD < _CD) {
        return;
    }
    // if(isOffScreen()) {
    //     _curCD = 0.f;
    // }
    if(this->getPos().y > 1000.f) {
        _curCD = 0.f;
    }

    if(this->getVelocity().y > 0) {
        this->setAniFrames(this->getFrames("Down"));
    }
    else {
        this->setAniFrames(this->getFrames("Up"));
    }
    Enemy::update();
}

void Podoboo::onEnemyCollision(Enemy& enemy) {
    return; // Podoboo does not interact with other enemies
}