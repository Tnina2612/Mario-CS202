#include<memory>
#include<unordered_map>
#include<string>
#include<iostream>

#include"../../assets/images/Coordinate.h"
#include"../../include/entities/Animation.hpp"
#include"../../include/entities/Enemy/EnemyFactory.hpp"
#include"../../include/entities/Enemy/Goomba.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/entities/Enemy/Plant.hpp"
#include"../../include/entities/Enemy/Koopa.hpp"

std::unordered_map<std::string, std::unordered_map<std::string, std::vector<Rectangle>>> EnemyFactory::s_enemyFrames;
std::shared_ptr<EnemyType> EnemyFactory::s_enemyTypes = nullptr;

void EnemyFactory::loadAllFrames() {
    s_enemyFrames["Goomba1"] = EnemySprite::Goomba::Map1::Frames;
    s_enemyFrames["Goomba2"] = EnemySprite::Goomba::Map2::Frames;
    s_enemyFrames["Goomba3"] = EnemySprite::Goomba::Map3::Frames;


    s_enemyFrames["Plant1"] = EnemySprite::PiranhaPlant::Map2::Frames;
    s_enemyFrames["Plant2"] = EnemySprite::PiranhaPlant::Map3::Frames;

    s_enemyFrames["Koopa1"] = EnemySprite::Koopa::Map1::Frames;
    s_enemyFrames["Koopa2"] = EnemySprite::Koopa::Map1::Frames;
    s_enemyFrames["Koopa3"] = EnemySprite::Koopa::Map1::Frames;
}

std::shared_ptr<Enemy> EnemyFactory::createEnemy(const std::string& name, Vector2 pos) {
    if(!s_enemyTypes) {
        s_enemyTypes = std::make_shared<EnemyType>();
    }

    if(name.find("Goomba") == 0) {
        auto it = std::make_shared<Goomba>(name, pos);
        it->setType(s_enemyTypes);
        it->setAllFrames(s_enemyFrames[name]);
        it->setAniFrames(it->getFrames("Walk"));
        it->setMovementStrategy(std::make_shared<DirectionMove>(it->getVelocity()));
        return it;
    }
    else if(name.find("Plant") == 0) {
        auto it = std::make_shared<Plant>(name, pos);
        it->setType(s_enemyTypes);
        it->setAllFrames(s_enemyFrames[name]);
        it->setAniFrames(it->getFrames("Walk"));
        it->setMovementStrategy(std::make_shared<DirectionMove>(it->getVelocity()));
        return it;
    }
    else if(name.find("Koopa") == 0) {
        auto it = std::make_shared<Koopa>(name, pos);
        it->setType(s_enemyTypes);
        it->setAllFrames(s_enemyFrames[name]);

        it->setAniFrames(it->getFrames("LWalk"));
        it->setMovementStrategy(std::make_shared<DirectionMove>(it->getVelocity()));
        
        if(name == "Koopa2") {
            it->setState(std::make_unique<WingedKoopa>());
        }
        //it->setState();
        return it;
        //return nullptr;
    }    
    
    return nullptr; 
}

