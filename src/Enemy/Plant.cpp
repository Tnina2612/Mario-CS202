#include<vector>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Plant.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"

#include<iostream>

Plant::Plant() : Enemy() {
    m_data._velocity = Vector2{0,50.f};
}

Plant::Plant(const std::string& name) : Enemy(name) {
    float width = 16.f;
    float height = 24.f;
    m_data = EnemyData (width, height, 0.f, false, false, true, false, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_data._velocity = Vector2{0, 50.f};

}

Plant::Plant(const std::string& name, Vector2 pos)
    : Plant(name) {
        m_data._pos = pos;
}

void Plant::update(float dt) {
    if(!m_data._isActive) {
        return;
    }
    Enemy::update(dt);
}

void Plant::onEnemyCollision(Enemy& enemy) {
    return; // Plant does not interact with other enemies
}

bool Plant::physics() {
    return false;
}