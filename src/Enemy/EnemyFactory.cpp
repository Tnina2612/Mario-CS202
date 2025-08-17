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
#include"../../include/entities/Enemy/Podoboo.hpp"
#include"../../include/entities/Enemy/Spiny.hpp"
#include"../../include/entities/Enemy/Lakitu.hpp"
#include"../../include/level/Level.hpp"



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

    s_enemyFrames["Podoboo"] = EnemySprite::Podoboo::Frames;
    s_enemyFrames["Spiny"] = EnemySprite::Spiny::Frames;
    s_enemyFrames["Lakitu"] = EnemySprite::Lakitu::Frames;
    // s_enemyFrames["Firebar"] = EnemySprite::Firebar::Frames;
}

std::shared_ptr<EnemyType>& EnemyFactory::getEnemyTypes() {
    if (!s_enemyTypes) {
        s_enemyTypes = std::make_shared<EnemyType>();
    }
    return s_enemyTypes;
}

std::shared_ptr<Enemy> EnemyFactory::createEnemy(const std::string& name, Vector2 pos, EnemyManager* enemyManager) {
    auto type = getEnemyTypes();
    if(name.find("Goomba") == 0) {
        auto it = std::make_shared<Goomba>(name, pos);
        it->setType(type);
        it->setAllFrames(s_enemyFrames[name]);
        it->setAniFrames(it->getFrames("Walk"));
        it->setMovementStrategy(std::make_shared<DirectionMove>());
        return it;
    }
    else if(name.find("Plant") == 0) {
        auto it = std::make_shared<Plant>(name, pos);
        it->setType(type);
        it->setAllFrames(s_enemyFrames[name]);
        it->setAniFrames(it->getFrames("Walk"));
        it->setMovementStrategy(std::make_shared<PlantMove>(enemyManager));
        return it;
    }
    else if(name.find("Koopa") == 0) {
        auto it = std::make_shared<Koopa>(name, pos, enemyManager);
        it->setType(type);
        it->setAllFrames(s_enemyFrames[name]);

        it->setAniFrames(it->getFrames("LWalk"));
        it->setMovementStrategy(std::make_shared<DirectionMove>());
        
        if(name == "Koopa2") {
            // it->setPreventFalling(true);
            it->setState(std::make_unique<WingedKoopa>());
        }
        //it->setState();
        return it;
        //return nullptr;
    }   
    else if(name.find("Podoboo") == 0) {
        auto it = std::make_shared<Podoboo>(name, pos);
        it->setType(type);
        it->setAllFrames(s_enemyFrames[name]);
        it->setAniFrames(it->getFrames("Up"));
        it->setMovementStrategy(std::make_shared<DirectionMove>());
        return it;
    }
    else if(name.find("Spiny") == 0) {
        auto it = std::make_shared<Spiny>(name, pos);
        it->setType(type);
        it->setAllFrames(s_enemyFrames[name]);
        it->setAniFrames(it->getFrames("Egg"));
        it->setMovementStrategy(std::make_shared<DirectionMove>());
        return it;
    }
    else if(name.find("Lakitu") == 0) {
        auto it = std::make_shared<Lakitu>(name, pos, enemyManager);
        it->setType(type);
        it->setAllFrames(s_enemyFrames[name]);
        it->setAniFrames(it->getFrames("Left"));
        it->setMovementStrategy(std::make_shared<LakituMove>());
        return it;
    }

    // else if(name.find("Firebar") == 0) {
    //     auto it = std::make_shared<Firebar>(name, pos);
    //     it->setType(s_enemyTypes);
    //     it->setAllFrames(s_enemyFrames[name]);
    //     it->setAniFrames(it->getFrames("Normal"));
    //     it->setMovementStrategy(std::make_shared<AngularMove>(it->getPos()));
    //     return it;
    // }
    
    return nullptr; 
}

std::vector<std::string> EnemyFactory::getEnemyTypesNames() {
    std::vector<std::string> names;
    for(const auto& pair : s_enemyFrames) {
        names.push_back(pair.first);
    }
    return names;
}