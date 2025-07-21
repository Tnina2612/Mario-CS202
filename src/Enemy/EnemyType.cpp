#include<memory>

#include"../include/entities/Enemy/EnemyType.hpp"


// EnemyType::EnemyType() {

// 
void EnemyType::setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy) {
    _movementStrategy = strategy;
}

std::shared_ptr<IEnemyStrategy> EnemyType::getMovementStrategy() {
    return _movementStrategy;
}

void EnemyType::draw() {

}
