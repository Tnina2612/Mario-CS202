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
    //EnemyType();
    EnemyType(const std::string& filepath);
    // EnemyType(Texture2D tex, std::shared_ptr<IEnemyStrategy> move)
    //     : _sprite(tex), _movementStrategy(move) {}
    void setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy);
    //void addCommand(std::unique_ptr<IEnemyCommand> command); //<for bosses
    void draw(Vector2 pos);
    std::shared_ptr<IEnemyStrategy> getMovementStrategy();
    
    virtual ~EnemyType();
};