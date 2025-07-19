#pragma once

#include<string>
#include<queue>
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

    std::string name;  //< Enemy name 

    Texture2D _sprite;
    Rectangle _hitBox;

    // const int _maxHp;
    float _baseSpeed;
    float _gravity;

    // int _curhp;              //<
    // bool _getHit;
    
    /*SFX
    AudioManager* manager
    */
    bool _isImuneFire;
    bool _isStompable;
    bool _isActive;

    std::shared_ptr<IEnemyStrategy> _movementStrategy;
    //std::queue<IEnemyCommand*> _commands; //<for bosses
public:
    //EnemyType();
    //EnemyType(const std::string& filepath);
    EnemyType(Texture2D tex, std::shared_ptr<IEnemyStrategy> move)
        : _sprite(tex), _movementStrategy(move) {}
    void setMovementStrategy(std::shared_ptr<IEnemyStrategy> strategy);
    //void addCommand(std::unique_ptr<IEnemyCommand> command); //<for bosses
    void draw();

    float getGravity();
    std::shared_ptr<IEnemyStrategy> getMovementStrategy();
    virtual ~EnemyType();
};