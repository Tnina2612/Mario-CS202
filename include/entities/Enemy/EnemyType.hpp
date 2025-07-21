#pragma once

#include<string>
#include<memory>
#include"raylib.h"

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

    // Vector2 _pos;         //<
    // Vector2 _velocity;
    // Vector2 _direction;

    // const int _maxHp;
    

    // int _curhp;              //<
    // bool _getHit;
    
    /*SFX
    AudioManager* manager
    */
    //std::queue<IEnemyCommand*> _commands; //<for bosses
    //bool _isActive;
    
    Texture2D _sprite;
    std::shared_ptr<IEnemyStrategy> _movementStrategy;
    
public:
    //EnemyType();
    //EnemyType(const std::string& filepath);
    EnemyType(Texture2D tex, std::shared_ptr<IEnemyStrategy> move)
        : _sprite(tex), _movementStrategy(move) {}
    void setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy);
    //void addCommand(std::unique_ptr<IEnemyCommand> command); //<for bosses
    void draw();
    std::shared_ptr<IEnemyStrategy> getMovementStrategy();
    
    virtual ~EnemyType();
};