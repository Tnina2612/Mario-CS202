#include<vector>
#include<cmath>
#include<memory>
#include<unordered_map>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Koopa.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/level/Level.hpp"
#include<core/Variables.hpp>

#include<iostream>
Koopa::Koopa() : Enemy() {
    m_state = std::make_unique<NormalKoopa>();
    m_data._velocity = LevelVar::KoopaSpeed;
}

Koopa::Koopa(const std::string& name) : Enemy(name) {
    float width = 16.f;
    float height = 24.f;
    m_data = EnemyData ( width, height, 10, false, true, true, false, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_state = std::make_unique<NormalKoopa>();
    m_data._velocity = LevelVar::KoopaSpeed;
}

Koopa::Koopa(const std::string& name, Vector2 pos, EnemyManager* enemyManager)
    : Koopa(name) {
        m_data._pos = pos;
        _enemyManager = enemyManager;
}

void Koopa::setState(std::unique_ptr<IKoopaState> state) {
    m_state = std::move(state);
    m_state->enter(*this);
}

void Koopa::setRecoveryTime(float t) {
    _recoveryTime = t;
}

bool Koopa::physics() {
    return true;
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

void Koopa::hitBlockLeft() {
    Enemy::hitBlockLeft();
    m_state->changeFrames(*this);
}

void Koopa::hitBlockRight() {
    Enemy::hitBlockRight();
    m_state->changeFrames(*this);
}

void Koopa::changeDirection() {
    Enemy::changeDirection();
    m_state->changeFrames(*this);
    // if(getDirection() == 1) {
    //     setAniFrames(getFrames("RWalk"));
    // }
    // else if(getDirection() == -1) {
    //     setAniFrames(getFrames("LWalk"));
    // }
}

bool Koopa::onHit() {
    if(!Enemy::onHit()) {
        return false;
    }
    if(!isAlive()) {
        setActive(false);
    }
    return true;
}

bool Koopa::beHitByFireball() {
    if(!Enemy::beHitByFireball()) {
        return false;
    }
    setState(std::make_unique<ShellKoopa>());
    m_data._hp--;
    return true;
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

void Koopa::hitVertical(int dir) {
    if(_inShell) {
        onStomp();
    }
}

bool Koopa::beHitVertical() {
    return _inShell && abs(getVelocity().x) <= pow(10,-5);
}

void NormalKoopa::changeFrames(Koopa& koopa) {
    if(koopa.getDirection() == 1) {
        koopa.setAniFrames(koopa.getFrames("RWalk"));
    }
    else if(koopa.getDirection() == -1) {
        koopa.setAniFrames(koopa.getFrames("LWalk"));
    }
}

void NormalKoopa::onEnemyCollision(Koopa& koopa, Enemy& other) {
    int oldDir = koopa.getDirection();

    koopa.changeDirection();

    float overlapX = std::min(koopa.getHitBox().x + koopa.getHitBox().width,
                              other.getHitBox().x + other.getHitBox().width)
                   - std::max(koopa.getHitBox().x, other.getHitBox().x);

    if (overlapX <= 0.0f) return;

    koopa.setPos(Vector2{koopa.getPos().x + overlapX * -oldDir, koopa.getPos().y});
}

void NormalKoopa::enter(Koopa& koopa) {
    auto f = koopa.getFrames("RWalk")[0];
    koopa.setEnemyData(EnemyData (  f.width, f.height, 1000.f, 
                                    false, true, true, false, 1, 
                                    koopa.getPos(), Vector2{0,0}, koopa.getDirection()));
    koopa.setVelocity(LevelVar::KoopaSpeed);
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
    std::cerr << koopa.m_data._isActive << std::endl;
    koopa.setState(std::make_unique<ShellKoopa>());
    std::cerr << koopa.m_data._isActive << std::endl;
}

void ShellKoopa::changeFrames(Koopa& koopa) {
    koopa.setAniFrames(koopa.getFrames("Shell2"));
}

void ShellKoopa::enter(Koopa& koopa) {
    if(koopa._enemyManager) {
        int dir = koopa._enemyManager->getPlayerPos().x < koopa.getPos().x ? 1 : -1;
        koopa.setDirection(dir);
    }
    auto f = koopa.getFrames("Shell1")[0];
    koopa.setEnemyData(EnemyData ( f.width, f.height, 1000.f, false, false, true, false, 1, 
                        koopa.getPos(), Vector2{0,0}, koopa.getDirection()));
    koopa.setRecoveryTime(0.f);
    koopa.setMovementStrategy(std::make_shared<DirectionMove>());
    koopa.setVelocity(Vector2{0.f, 0.f});
    koopa.setAniFrames(koopa.getFrames("Shell2"));
    koopa.setInShell(true);
}

void ShellKoopa::update(Koopa& koopa, float dt) {
    if(abs(koopa.getVelocity().x) <= pow(10,-5))
        koopa.setRecoveryTime(koopa.getRecoveryTime() + dt);

    if(koopa.getRecoveryTime() > koopa.TIME) {
        koopa.setState(std::make_unique<NormalKoopa>());
    }
    else if(koopa.getRecoveryTime() > koopa.TIME - 1.f) {
        koopa.setAniFrames(koopa.getFrames("Shell1"));
    }
}

void ShellKoopa::handleStomp(Koopa& koopa) {
    if(abs(koopa.getVelocity().x) <= pow(10,-5)) {
        Vector2 temp = {150.f, 0.f};
        koopa.setVelocity(temp);
        koopa.setAniFrames(koopa.getFrames("Shell2"));
        koopa.setRecoveryTime(0);

        if(koopa._enemyManager) {
            int dir = koopa._enemyManager->getPlayerPos().x < koopa.getPos().x ? 1 : -1;
            koopa.setDirection(dir);
        }
    }
    else {
        koopa.setVelocity(Vector2{0.f,0.f});
    }
}

void ShellKoopa::onEnemyCollision(Koopa& koopa, Enemy& other) {
    if(abs(koopa.getVelocity().x) < pow(10, -3)) {
        return;
    }
    other.onHit();
}

void WingedKoopa::changeFrames(Koopa& koopa) {
    if(koopa.getDirection() == 1) {
        koopa.setAniFrames(koopa.getFrames("RWWalk"));
    }
    else if(koopa.getDirection() == -1) {
        koopa.setAniFrames(koopa.getFrames("LWWalk"));
    }
}

void WingedKoopa::enter(Koopa& koopa) {
    auto f = koopa.getFrames("RWWalk")[0];

    koopa.setEnemyData(EnemyData (f.width, f.height, 1000.f, false, true, true, false, 1, 
                        koopa.getPos(), Vector2{0,0}, koopa.getDirection()));
    koopa.setVelocity(LevelVar::KoopaSpeed);
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
    int oldDir = koopa.getDirection();

    koopa.changeDirection();

    float overlapX = std::min(koopa.getHitBox().x + koopa.getHitBox().width,
                              other.getHitBox().x + other.getHitBox().width)
                   - std::max(koopa.getHitBox().x, other.getHitBox().x);

    if (overlapX <= 0.0f) return;

    koopa.setPos(Vector2{koopa.getPos().x + overlapX * -oldDir, koopa.getPos().y});
}