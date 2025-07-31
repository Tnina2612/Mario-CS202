#pragma once

#include<string>
#include"raylib.h"

class EnemyType {
public:
    Texture2D sprite;
    EnemyType(const std::string& path = "./assets/images/sprite-sheets/enemies.png");    
    virtual ~EnemyType();
};