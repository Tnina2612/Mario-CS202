#include "level/Level.hpp"

Level_1_1_Ground::Level_1_1_Ground() : background("./world-maps/1-1-Ground/background.txt")/*, blocks("./world-maps/1-1-Ground/blocks.txt")*/ {
    player = make_shared<Mario>();

    // {
    //     EnemyFactory::loadAllFrames();
    //     ifstream inp("./world-maps/1-1-Ground/enemies.txt");
    //     int numTypes;
    //     inp >> numTypes;
    //     for(int i = 0; i < numTypes; i++) {
    //         int numEnemies;
    //         inp >> numEnemies;
    //         string enemyType;
    //         inp >> enemyType;
    //         for(int j = 0; j < numEnemies; j++) {
    //             int y, x; 
    //             inp >> y >> x;
    //             float posX = x * BLOCKSIDE;
    //             float posY = y * BLOCKSIDE;
    //             enemies.push_back(EnemyFactory::createEnemy(enemyType, Vector2{posX, posY}));
    //         }
    //     }
    //     inp.close();
    // }
}

void Level_1_1_Ground::draw(void) {
    cout << "Draw background\n";
    background.draw();
    // blocks.draw();
    // player->draw();
    // for(std::shared_ptr<Enemy> enemy : enemies) {
    //     enemy->draw();
    // }
}

void Level_1_1_Ground::update(void) {
    // blocks.update(player);
    player->update();
}

float Level_1_1_Ground::getWidth(void) { return background.getWidth(); }
float Level_1_1_Ground::getHeight(void) { return background.getHeight(); }
std::shared_ptr<Character> Level_1_1_Ground::getCharacter() { return player; }