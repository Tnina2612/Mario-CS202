#pragma once

#include<memory>
#include<string>
#include<unordered_map>
#include"raylib.h"

#include"EnemyType.hpp"
#include"EnemyData.hpp"
#include"IEnemyStrategy.hpp"
#include"../include/entities/Animation.hpp"

class Enemy {
protected:
    Animation m_animation;
    EnemyData m_data;
    std::unordered_map<std::string, std::vector<Rectangle>> allFrames;
public:
    Enemy();
    Enemy(const std::string& name);
    Enemy(const std::string& name, Vector2 pos);
    //Enemy(std::shared_ptr<EnemyType> type, Vector2 pos);

    void setActive(bool isActive);
    void setAllFrames(std::unordered_map<std::string, std::vector<Rectangle>> frames);
    void setAniFrames(const std::vector<Rectangle>& frames);
    void setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy);
    void setType(std::shared_ptr<EnemyType> type);
    void setEnemyData(const EnemyData& data);
    void setDirection(int dir);
    void setVelocity(Vector2 v);

    int getDirection();
    Vector2 getVelocity();
    Vector2 getPos();
    std::vector<Rectangle> getFrames(const std::string& name);
    bool isAlive();
    int isOffScreen(); //-1 : up, 1 : down, 2 : right, -2 : left 
    virtual bool onHit();
    virtual bool onStomp();
    virtual bool beHitByFireball();

    virtual void draw(); 
    virtual void update(float dt = GetFrameTime());

    virtual~Enemy() =default;
};