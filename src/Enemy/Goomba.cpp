#include<vector>
#include<iostream>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Goomba.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"



Goomba::Goomba() : Enemy() {
    _deadAni = 0;
    m_data._velocity = Vector2{-100, 0.f};
}

Goomba::Goomba(const std::string& name) : Enemy(name) {
    _deadAni = 0;
    float width = 16.f;
    float height = 16.f;
    m_data = EnemyData (width, height, 10, false, true, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_data._velocity = Vector2{-100, 0.f};
    
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
            setVelocity(Vector2{0.f, 500.f});
            //setMovementStrategy(std::make_shared<DirectionMove>(Vector2{0, 500.f}));
            _deadAni = 1;
        }
        if(isOffScreen() == 1 || isOffScreen() == -2) {
            _deadAni = -1;
        }

        if(_deadAni == -1) {
            setActive(false);
        }
        std::cerr << "OKE2" << std::endl;
        return true;
    }
    return true;
}
void Goomba::update(float dt) {
    std::cerr << "OKE1" << std::endl;
    Enemy::update(dt);
    std::cerr << "OKE" << std::endl;
    // time += dt;
    // if(time > 1.2f) {
    //     this->onHit();
    // }
}

// void Goomba::draw() {
//     if(!m_data._isActive || !isAlive()) {
//         return;
//     }
//     Enemy::draw();
// }