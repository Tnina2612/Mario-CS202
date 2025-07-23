#pragma once

#include<memory>
#include<string>
#include"raylib.h"

#include"EnemyType.hpp"
#include"EnemyData.hpp"
#include"../include/entities/Animation.hpp"

class Enemy {
protected:
    EnemyData m_data;
    //Animation m_animation;
    //int _direction; // 1 right, -1 left
    
public:
    //Enemy(EnemyData data, Animation ani) : m_data(data), m_animation(ani) {}

    std::shared_ptr<EnemyType> getEnemyType();
    Vector2 getBaseSpeed();
    //Vector2 getVelocity();
    void setVelocity(Vector2 vel);
    void setActive(bool isActive);
    bool isAlive();

    virtual void init(std::shared_ptr<EnemyType> newType, Vector2 startPosition);

    virtual bool onHit();
    virtual bool onStomp();
    virtual bool beHitByFireball();

    virtual void draw(); 
    virtual void update(float dt);
};