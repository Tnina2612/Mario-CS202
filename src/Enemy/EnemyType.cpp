#include<string>
#include<memory>

#include"../../include/entities/Enemy/EnemyType.hpp"

void EnemyType::setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy) {
    _movementStrategy = strategy;
}

std::shared_ptr<IEnemyStrategy> EnemyType::getMovementStrategy() {
    return _movementStrategy;
}

void EnemyType::draw(Vector2 pos) {
    m_animation.draw(pos);
}

EnemyType::EnemyType(const std::string& filepath) {
    LoadTexture(filepath.c_str());
}

EnemyType::~EnemyType() {
    UnloadTexture(m_animation.sprite);
}