#pragma once

#include<memory>
#include<string>
#include"raylib.h"

#include"EnemyType.hpp"
#include"EnemyData.hpp"
#include"IEnemyStrategy.hpp"
#include"../include/entities/Animation.hpp"

class Enemy {
protected:
    Animation m_animation;
    EnemyData m_data;
public:
    Enemy();
    Enemy(const std::string& name);
    Enemy(const std::string& name, Vector2 pos);
    //Enemy(std::shared_ptr<EnemyType> type, Vector2 pos);

    void setActive(bool isActive);
    void setFrames(const std::vector<Rectangle>& frames);
    void setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy);
    void setType(std::shared_ptr<EnemyType> type);
    bool isAlive();

    virtual bool onHit();
    virtual bool onStomp();
    virtual bool beHitByFireball();

    virtual void draw(); 
    virtual void update(float dt = GetFrameTime());

    virtual~Enemy() =default;
};