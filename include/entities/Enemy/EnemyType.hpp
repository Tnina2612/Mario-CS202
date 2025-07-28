#pragma once

#include<vector>
#include<string>
#include<memory>
#include"raylib.h"

#include"../include/entities/Animation.hpp"
#include"IEnemyStrategy.hpp"

class EnemyType {
// protected:
//     std::shared_ptr<IEnemyStrategy> _movementStrategy;
public:
    Texture2D sprite;
    EnemyType(const std::string& path = "./assets/images/sprite-sheets/enemies.png");
    //void setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy);
    //void update(float dt, Vector2& pos);
    
    virtual ~EnemyType();
};