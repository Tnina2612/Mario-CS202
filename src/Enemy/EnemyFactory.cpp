#include<memory>
#include<unordered_map>
#include<string>

#include"../../include/entities/Enemy/EnemyFactory.hpp"

std::unordered_map<std::string, std::shared_ptr<EnemyType>> EnemyFactory::s_enemyTypes;
std::shared_ptr<DirectionMove> EnemyFactory::s_directionMove = std::make_shared<DirectionMove>();
std::shared_ptr<JumpMove> EnemyFactory::s_jumpMove = std::make_shared<JumpMove>();

std::shared_ptr<EnemyType> EnemyFactory::getEnemyType(const std::string& name) {
    if(s_enemyTypes.count(name)) {
        return s_enemyTypes[name];
    }
    std::string path = "./assets/images/sprite-sheets/enemies.png";

    if(name == "Goomba1") {
        // Texture2D tex = LoadTexture("goomba.png");
        // s_enemyTypes[name] = std::make_shared<EnemyType>(tex, s_directionMove);
    }
    else if(name == "Goomba2") {
        // Texture2D tex = LoadTexture("koopa.png");
        // s_enemyTypes[name] = std::make_shared<EnemyType>(tex, s_directionMove);
    }
    else if(name == "Goomba3") {
        // Texture2D tex = LoadTexture("koopa.png");
        // s_enemyTypes[name] = std::make_shared<EnemyType>(tex, s_directionMove);
    }
    else if(name == "Koopa") {
        // Texture2D tex = LoadTexture("koopa.png");
        // s_enemyTypes[name] = std::make_shared<EnemyType>(tex, s_directionMove);
    }
    // else if(name == "" ){

    // }

    
    return s_enemyTypes[name];
}

