#pragma once

#include<memory>
#include<string>
#include"raylib.h"

#include"EnemyType.hpp"
#include"EnemyData.hpp"

class Enemy {
private:
    EnemyData m_data;
    //int _direction; // 1 right, -1 left
    
public:
    Enemy(EnemyData data) : m_data(data) {}
    std::shared_ptr<EnemyType> getEnemyType();
    Vector2 getBaseSpeed();
    void init(std::shared_ptr<EnemyType> newType, Vector2 startPosition);
    virtual void draw(); 
    virtual void update(float dt);
};