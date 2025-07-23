#include<memory>
#include<unordered_map>
#include<string>
#include<iostream>

#include"../../assets/images/Coordinate.h"
#include"../../include/entities/Animation.hpp"
#include"../../include/entities/Enemy/EnemyFactory.hpp"
#include"../../include/entities/Enemy/Goomba.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"

std::unordered_map<std::string, std::vector<Rectangle>> EnemyFactory::s_enemyFrames;
std::shared_ptr<EnemyType> EnemyFactory::s_enemyTypes = nullptr;

void EnemyFactory::loadAllFrames() {
    s_enemyFrames["Goomba1"] = EnemySprite::Goomba::Map1::Frames;
    s_enemyFrames["Goomba2"] = EnemySprite::Goomba::Map2::Frames;
    s_enemyFrames["Goomba3"] = EnemySprite::Goomba::Map3::Frames;

    // s_enemyFrames["Koopa1"] = EnemySprite::Koopa::Map1::Frames;
    // s_enemyFrames["Koopa2"] = EnemySprite::Koopa::Map2::Frames;
    // s_enemyFrames["Koopa3"] = EnemySprite::Koopa::Map3::Frames;

}

std::shared_ptr<Enemy> EnemyFactory::createEnemy(const std::string& name, Vector2 pos) {
    if(!s_enemyTypes) {
        s_enemyTypes = std::make_shared<EnemyType>();
    }

    if(name.rfind("Goomba") == 0) {
        auto it = std::make_shared<Goomba>(name, pos);
        it->setType(s_enemyTypes);
        it->setFrames(s_enemyFrames[name]);
        it->setMovementStrategy(std::make_shared<DirectionMove>());
        return it;
    }

    else if(name.rfind("Koopa") == 0) {
        return nullptr;
    }    
    
    return nullptr; 
}

