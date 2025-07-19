#include<memory>

#include"../include/entities/Enemy/EnemyFactory.hpp"


std::shared_ptr<EnemyType> EnemyFactory::getEnemyType(const std::string& name) {
    if(enemyTypes.count(name)) {
        return enemyTypes[name];
    }

    if(name == "Goomba") {
        Texture2D tex = LoadTexture("goomba.png");
        enemyTypes[name] = std::make_shared<EnemyType>(tex, directionMove);
    }
    else if(name == "Koopa") {
        Texture2D tex = LoadTexture("koopa.png");
        enemyTypes[name] = std::make_shared<EnemyType>(tex, directionMove);
    }
    // else if(name == "" ){

    // }

    
    return enemyTypes[name];
}

