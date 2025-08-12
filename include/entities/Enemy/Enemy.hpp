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
    std::shared_ptr<IEnemyStrategy> _movementStrategy;
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
    void setOnGround(bool onGround);

    std::shared_ptr<IEnemyStrategy> getMovementStrategy();
    EnemyData& getEnemyData();
    float getGravity();
    bool getOnGround();

    int getDirection();
    std::vector<Rectangle> getFrames(const std::string& name);
    
    void applyGravity(float dt);
    bool isAlive();
    int isOffScreen(); //-1 : up, 1 : down, 2 : right, -2 : left 

    virtual bool onHit();
    virtual bool onStomp();
    virtual void changeDirection();
    
    virtual Rectangle getHitBox();       //<Define the hitbox of the enemy

    virtual void hitBlockLeft();         //< hit by block on the left
    virtual void hitBlockRight();        //< hit by block on the right
    virtual void hitBlockDown();         //< hit by block beneath
    virtual void hitUp();                //< hit by character from above
    virtual bool beHitByFireball();      //< fireball

    virtual void onEnemyCollision(Enemy& enemy) = 0; //< collision with other enemies
    virtual bool physics() = 0;                        //< physics
    Vector2 getVelocity();
    Vector2 getPos();

    void setVelocity(Vector2 v);
    void setVelocityX(float x);
    void setVelocityY(float y);
    void setPos(Vector2 pos);
    float getRestVelocity()const;

    virtual void draw(); 
    virtual void update(float dt = GetFrameTime());
    std::string getTypeName() const;

    virtual~Enemy() =default;
};