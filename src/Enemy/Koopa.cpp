#include<vector>
#include<cmath>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Koopa.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"
#include<core/Variables.hpp>

#include<iostream>
Koopa::Koopa() : Enemy() {
    m_state = std::make_unique<NormalKoopa>();
    m_data._velocity = LevelVar::KoopaSpeed;
}

Koopa::Koopa(const std::string& name) : Enemy(name) {
    float width = 16.f;
    float height = 16.f;
    m_data = EnemyData ( width, height, 10, false, true, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_state = std::make_unique<NormalKoopa>();
    m_data._velocity = LevelVar::KoopaSpeed;
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
    else {
        if(_deadAni == 0) {
            _deadAni = 1;
        }
        else if(_deadAni == 1) {
            _deadAni = -1;
        }
        else if(_deadAni == -1) {
            setActive(false);
        }


    }

    // else {

    // }
}
// bool Koopa::onHit() {

// }

void Koopa::changeDirection() {
    
}

bool Koopa::setInShell(bool inShell) {
    _inShell = inShell;
    return _inShell;
}

bool Koopa::onStomp() {
    m_state->handleStomp(*this);
    return true;
}

void Koopa::onEnemyCollision(Enemy& enemy) {
    m_state->onEnemyCollision(*this, enemy);
}

// bool Koopa::beHitByFireball() {

// }
// void Koopa::draw() {
//     if(!m_data._isActive || !isAlive()) {
//         return;
//     }
//     Enemy::draw();
// }

void NormalKoopa::onEnemyCollision(Koopa& koopa, Enemy& other) {
    koopa.changeDirection();
    if(koopa.getDirection() == 1) {
        koopa.setAniFrames(koopa.getFrames("RWalk"));
    }
    else if(koopa.getDirection() == -1) {
        koopa.setAniFrames(koopa.getFrames("LWalk"));
    }
}

void NormalKoopa::enter(Koopa& koopa) {
    koopa.setEnemyData(EnemyData (  koopa.getHitBox().width, koopa.getHitBox().height, 10, 
                                    false, true, true, 1, 
                                    koopa.getPos(), Vector2{0,0}, -1));
    koopa.setVelocity(Vector2{-50.f, 0.f});
    koopa.setMovementStrategy(std::make_shared<DirectionMove>());
    koopa.setInShell(false);
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
    koopa.setEnemyData(EnemyData ( koopa.getHitBox().width, koopa.getHitBox().height, 10, false, false, true, 1, 
                        koopa.getPos(), Vector2{0,0}, -1));
    koopa.setRecoveryTime(0.f);
    koopa.setMovementStrategy(std::make_shared<DirectionMove>());
    koopa.setVelocity(Vector2{0.f, 0.f});
    koopa.setAniFrames(koopa.getFrames("Shell1"));
    koopa.setInShell(true);
}

void ShellKoopa::update(Koopa& koopa, float dt) {
    if(abs(koopa.getVelocity().x) <= pow(10,-5))
        koopa.setRecoveryTime(koopa.getRecoveryTime() + dt);

    if(koopa.getRecoveryTime() > koopa.TIME) {
        koopa.setState(std::make_unique<NormalKoopa>());
    }
    else if(koopa.getRecoveryTime() > koopa.TIME - 1.f) {
        koopa.setAniFrames(koopa.getFrames("Shell2"));
    }
}

void ShellKoopa::handleStomp(Koopa& koopa) {
    if(abs(koopa.getVelocity().x) <= pow(10,-5)) {
        Vector2 temp = {-150.f*koopa.getDirection(), 0.f};
        koopa.setVelocity(temp);
        koopa.setMovementStrategy(std::make_shared<DirectionMove>());
        koopa.setRecoveryTime(0);
    }
    else {
        koopa.setVelocity(Vector2{0.f,0.f});
        koopa.setMovementStrategy(std::make_shared<DirectionMove>());
    }
}

void ShellKoopa::onEnemyCollision(Koopa& koopa, Enemy& other) {
    if(koopa.getVelocity().x < pow(10, -3)) {
        return;
    }
    other.onHit();
}

void WingedKoopa::enter(Koopa& koopa) {
    koopa.setEnemyData(EnemyData (koopa.getHitBox().width, koopa.getHitBox().height, 10, false, true, true, 1, 
                        koopa.getPos(), Vector2{0,0}, -1));
    koopa.setVelocity(Vector2{-100.f, 100.f});
    koopa.setMovementStrategy(std::make_shared<JumpMove>());
    koopa.setInShell(false);
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

void WingedKoopa::onEnemyCollision(Koopa& koopa, Enemy& other) {
    koopa.changeDirection();
    if(koopa.getDirection() == 1) {
        koopa.setAniFrames(koopa.getFrames("RWWalk"));
    }
    else if(koopa.getDirection() == -1) {
        koopa.setAniFrames(koopa.getFrames("LWWalk"));
    }
}