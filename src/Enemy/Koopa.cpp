#include<vector>
#include<cmath>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Koopa.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"

#include<iostream>
Koopa::Koopa() : Enemy() {
    m_state = std::make_unique<NormalKoopa>();
    m_data._velocity = Vector2{-100, 0.f};
}

Koopa::Koopa(const std::string& name) : Enemy(name) {
    Rectangle hitbox = {0,0,1,1};
    m_data = EnemyData ( hitbox, 10, false, true, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_state = std::make_unique<NormalKoopa>();
    m_data._velocity = Vector2{-100, 0.f};
}

Koopa::Koopa(const std::string& name, Vector2 pos)
    : Koopa(name) {
        m_data._pos = pos;
}

void Koopa::setState(std::unique_ptr<IKoopaState> state) {
    m_state = std::move(state);
    m_state->enter(*this);
}

void Koopa::setRecoveryTime(float t) {
    _recoveryTime = t;
}

float Koopa::getRecoveryTime() {
    return _recoveryTime;
}

void Koopa::update(float dt) {
    if(!m_data._isActive || !isAlive()) {
        return;
    }

    if(this->isAlive()) {
        m_state->update(*this, dt);
        Enemy::update(dt);
    }

    // else {

    // }
}
// bool Koopa::onHit() {

// }

bool Koopa::onStomp() {
    m_state->handleStomp(*this);
    return true;
}

// bool Koopa::beHitByFireball() {

// }
// void Koopa::draw() {
//     if(!m_data._isActive || !isAlive()) {
//         return;
//     }
//     Enemy::draw();
// }

void NormalKoopa::enter(Koopa& koopa) {
    Rectangle hitbox = {0,0,1,1};
    koopa.setEnemyData(EnemyData ( hitbox, 10, false, true, true, 1, 
                        koopa.getPos(), Vector2{0,0}, -1));
    koopa.setVelocity(Vector2{-50.f, 0.f});
    koopa.setMovementStrategy(std::make_shared<DirectionMove>(koopa.getVelocity()));
    if(koopa.getDirection() == 1) {
        koopa.setAniFrames(koopa.getFrames("RWalk"));
    }
    else if(koopa.getDirection() == -1) {
        koopa.setAniFrames(koopa.getFrames("LWalk"));
    }
}

void NormalKoopa::update(Koopa& koopa, float dt) {
    return;
}

void NormalKoopa::handleStomp(Koopa& koopa) {
    koopa.setState(std::make_unique<ShellKoopa>());
}

void ShellKoopa::enter(Koopa& koopa) {
    Rectangle hitbox = {0,0,1,1};
    koopa.setEnemyData(EnemyData ( hitbox, 10, false, false, true, 1, 
                        koopa.getPos(), Vector2{0,0}, -1));
    koopa.setRecoveryTime(0.f);
    koopa.setMovementStrategy(std::make_shared<DirectionMove>(Vector2{0.f,0.f}));
    koopa.setAniFrames(koopa.getFrames("Shell"));
}

void ShellKoopa::update(Koopa& koopa, float dt) {
    if(abs(koopa.getVelocity().x) <= pow(10,-5))
        koopa.setRecoveryTime(koopa.getRecoveryTime() + dt);

    if(koopa.getRecoveryTime() > koopa.TIME) {
        koopa.setState(std::make_unique<NormalKoopa>());
    }
}

void ShellKoopa::handleStomp(Koopa& koopa) {
    if(abs(koopa.getVelocity().x) <= pow(10,-5)) {
        Vector2 temp = {-50.f*koopa.getDirection(), 0.f};
        koopa.setVelocity(temp);
        koopa.setMovementStrategy(std::make_shared<DirectionMove>(koopa.getVelocity()));
        koopa.setRecoveryTime(0);
    }
    else {
        koopa.setVelocity(Vector2{0.f,0.f});
        koopa.setMovementStrategy(std::make_shared<DirectionMove>(koopa.getVelocity()));
    }
}


void WingedKoopa::enter(Koopa& koopa) {

    Rectangle hitbox = {0,0,1,1};
    koopa.setEnemyData(EnemyData ( hitbox, 10, false, true, true, 1, 
                        koopa.getPos(), Vector2{0,0}, -1));
    koopa.setVelocity(Vector2{-100.f, 100.f});
    koopa.setMovementStrategy(std::make_shared<JumpMove>(koopa.getVelocity()));
    if(koopa.getDirection() == 1) {
        koopa.setAniFrames(koopa.getFrames("RWWalk"));
    }
    else if(koopa.getDirection() == -1) {
        koopa.setAniFrames(koopa.getFrames("LWWalk"));
    }
}

void WingedKoopa::update(Koopa& koopa, float dt) {
    return;
}

void WingedKoopa::handleStomp(Koopa& koopa) {
    koopa.setState(std::make_unique<NormalKoopa>());
}
