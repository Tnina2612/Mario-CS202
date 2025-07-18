#pragma once

#include<string>
#include<queue>
#include<memory>
#include"raylib.h"

#include"IEnemyStrategy.hpp"


class EnemyType {
private:

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

    const std::string name;  //< Enemy name 

    Texture2D _sprite;
    Rectangle _hitBox;

    // const int _maxHp;
    const float _baseSpeed;
    const float _gravity;

    // int _curhp;              //<
    // bool _getHit;
    
    /*SFX
    AudioManager* manager
    */
    bool _isImuneFire;
    bool _isStompable;
    bool _isActive;

    std::unique_ptr<IEnemyStrategy> movementStrategy;
    //std::queue<IEnemyCommand*> _commands; //<for bosses
public:
    EnemyType();
    EnemyType(const std::string& filepath);
    
    void setMovementStrategy(std::unique_ptr<IEnemyStrategy> strategy);
    //void addCommand(std::unique_ptr<IEnemyCommand> command); //<for bosses
    void draw();

    virtual ~EnemyType();
};