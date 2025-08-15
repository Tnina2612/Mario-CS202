#include<cmath>

#include"../../include/entities/Enemy/Lakitu.hpp"
#include"../../include/entities/Enemy/Spiny.hpp"
#include"../../include/entities/Enemy/EnemyFactory.hpp"
#include"../../include/level/Level.hpp"



Lakitu::Lakitu() : Enemy() {
    m_data._velocity = Vector2{40.f, 0.f};
}

Lakitu::Lakitu(const std::string& name) : Lakitu() {
    float width = 16.f;
    float height = 16.f;
    m_data = EnemyData (width, height, 0.f, false, true, true, false, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);

    m_data._velocity = Vector2{40.f, 0.f};
}

Lakitu::Lakitu(const std::string& name, Vector2 pos, EnemyManager* enemyManager) 
    : Lakitu(name) {

    _enemyManager = enemyManager;
    m_data._pos = pos;
}

void Lakitu::onEnemyCollision(Enemy& enemy) {
    // Handle collision with other enemies
}

void Lakitu::hitBlockLeft() {
    Enemy::hitBlockLeft();
}

void Lakitu::hitBlockRight() {
    Enemy::hitBlockRight();
}

bool Lakitu::physics() {
    return true;
}

void Lakitu::spawnSpiny() {
    if (_enemyManager) {
        auto spiny = EnemyFactory::createEnemy("Spiny", {m_data._pos.x -30.f * sinf((float) GetTime()), m_data._pos.y}, _enemyManager);
        _enemyManager->addEnemy(spiny);
        spiny->setActive(true);
    }
}

void Lakitu::update(float dt) {
    Enemy::update(dt);
    spawnTimer += dt;
    if (spawnTimer >= _cd) {
        spawnSpiny();
        spawnTimer = 0.f;
    }

    if(_enemyManager) {
        Vector2 pos = _enemyManager->getPlayerPos();
        m_data._targetPos = pos;
    }
}