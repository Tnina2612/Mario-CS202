#include<string>
#include<memory>
#include"raylib.h"
#include<iostream>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../include/entities/Animation.hpp"
#include"../../include/entities/Enemy/IEnemyStrategy.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"


EnemyType::EnemyType(const std::string& path)   
{
    sprite = LoadTexture(path.c_str());
}

EnemyType::~EnemyType() {
    UnloadTexture(sprite);
}