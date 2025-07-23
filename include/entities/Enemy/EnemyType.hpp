#pragma once

#include<vector>
#include<string>
#include<memory>
#include"raylib.h"

#include"../include/entities/Animation.hpp"
#include"IEnemyStrategy.hpp"

class EnemyType {
protected:

// enum EnemyType {
//     Goomba,
//     KoopaTroopa,
//     KoopaParatroopa,
//     BuzzyBeetle,
//     Spiny,
//     PiranhaPlant
// };
    //std::queue<IEnemyCommand*> _commands; //<for bosses

    Animation m_animation;
    std::shared_ptr<IEnemyStrategy> _movementStrategy;
    
public:
    EnemyType(Animation& animation, std::shared_ptr<IEnemyStrategy> strategy)
        : m_animation(animation), _movementStrategy(strategy) {}
    EnemyType(const std::string& path = "./assets/images/sprite-sheets/enemies.png");

    void setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy);
    //void addCommand(std::unique_ptr<IEnemyCommand> command); //<for bosses
    void setFrames(std::vector<Rectangle> frames);
    void draw(Vector2 pos);
    void update(float dt, Vector2& pos);
    
    virtual ~EnemyType();
};