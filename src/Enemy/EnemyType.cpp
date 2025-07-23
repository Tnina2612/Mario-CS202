#include<string>
#include<memory>
#include"raylib.h"
#include<iostream>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../include/entities/Animation.hpp"
#include"../../include/entities/Enemy/IEnemyStrategy.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"


EnemyType::EnemyType(const std::string& path)   
    :  _movementStrategy(nullptr)
{
    sprite = LoadTexture(path.c_str());
}

void EnemyType::setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy) {
    _movementStrategy = strategy;
}

// void EnemyType::draw(Vector2 pos) {
//     std::cerr << " 5" <<std::endl;
//     try {
//         std::cerr << "sprite.id = " << m_animation.sprite.id << std::endl;
//     } catch(...) {
//         std::cerr << "exception when accessing sprite.id" << std::endl;
//     }
//     m_animation.draw(pos);
// }

EnemyType::~EnemyType() {
    UnloadTexture(sprite);
}

void EnemyType::update(float dt, Vector2& pos) {
    if(_movementStrategy)
        _movementStrategy->Execute(pos, dt);
}