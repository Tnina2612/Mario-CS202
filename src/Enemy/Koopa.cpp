#include<vector>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Koopa.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"


Koopa::Koopa() : Enemy() {
    m_state = std::make_unique<NormalKoopa>();
}

Koopa::Koopa(const std::string& name) : Enemy(name) {
    Rectangle hitbox = {0,0,1,1};
    m_data = EnemyData ( hitbox, 10, false, true, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_state = std::make_unique<ShellKoopa>();
    
}

Koopa::Koopa(const std::string& name, Vector2 pos)
    : Koopa(name) {
        m_data._pos = pos;
}

void Koopa::setState(std::unique_ptr<IKoopaState> state) {
    m_state = std::move(state);
    m_state->enter(*this);
}

void Koopa::setRecoveryTime(int t) {
    _recoveryTime = t;
}

int Koopa::getRecoveryTime() {
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

// void Koopa::draw() {
//     if(!m_data._isActive || !isAlive()) {
//         return;
//     }
//     Enemy::draw();
// }

void NormalKoopa::enter(Koopa& koopa) {
    Rectangle hitbox = {0,0,1,1};
    koopa.setEnemyData(EnemyData ( hitbox, 10, false, true, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1));
}

void NormalKoopa::update(Koopa& koopa, float dt) {}

void NormalKoopa::handleStomp(Koopa& koopa) {
    koopa.setState(std::make_unique<ShellKoopa>());
}

void ShellKoopa::enter(Koopa& koopa) {
    Rectangle hitbox = {0,0,1,1};
    koopa.setEnemyData(EnemyData ( hitbox, 10, false, false, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1));
    
}

void ShellKoopa::update(Koopa& koopa, float dt) {
    koopa.setRecoveryTime(koopa.getRecoveryTime() - dt);

    if(koopa.getRecoveryTime() > koopa.TIME) {
        koopa.setState(std::make_unique<NormalKoopa>());
    }
}

void ShellKoopa::handleStomp(Koopa& koopa) {
    if(koopa.getVelocity().x == 0) {
        Vector2 temp = {100.f*koopa.getDirection(), 0.f};
        koopa.setMovementStrategy(std::make_shared<DirectionMove>(temp));
        koopa.setRecoveryTime(0);
    }
    else {
        koopa.setMovementStrategy(std::make_shared<DirectionMove>(Vector2{0.f,0.f}));
    }
}


void WingedKoopa::enter(Koopa& koopa) {
    Rectangle hitbox = {0,0,1,1};
    koopa.setEnemyData(EnemyData ( hitbox, 10, false, true, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1));
    koopa.setMovementStrategy(std::make_shared<JumpMove>());
}

void WingedKoopa::update(Koopa& koopa, float dt) {}

void WingedKoopa::handleStomp(Koopa& koopa) {
    koopa.setState(std::make_unique<NormalKoopa>());
}
