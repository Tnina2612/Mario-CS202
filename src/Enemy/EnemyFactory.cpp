#include<memory>

#include"../include/entities/Enemy/EnemyFactory.hpp"

std::unordered_map<std::string, std::shared_ptr<EnemyType>> EnemyFactory::s_enemyTypes;
std::shared_ptr<DirectionMove> EnemyFactory::s_directionMove = std::make_shared<DirectionMove>();
std::shared_ptr<JumpMove> EnemyFactory::s_jumpMove = std::make_shared<JumpMove>();

std::shared_ptr<EnemyType> EnemyFactory::getEnemyType(const std::string& name) {
    if(s_enemyTypes.count(name)) {
        return s_enemyTypes[name];
    }

    if(name == "Goomba") {
        Texture2D tex = LoadTexture("goomba.png");
        s_enemyTypes[name] = std::make_shared<EnemyType>(tex, s_directionMove);
    }
    else if(name == "Koopa") {
        Texture2D tex = LoadTexture("koopa.png");
        s_enemyTypes[name] = std::make_shared<EnemyType>(tex, s_directionMove);
    }
    // else if(name == "" ){

    // }

    
    return s_enemyTypes[name];
}

