#include "level/Level.hpp"

Level::Level(const std::string& fileName) : inputManager(INPUT_MANAGER) {
    tileMap = std::make_shared<TileMap>(fileName);
    player = std::make_shared<Mario>();
    inputManager.addCharacter(player.get());

    inputManager.addKey(KEY_LEFT);
    inputManager.addKey(KEY_RIGHT);
    inputManager.addKey(KEY_UP);
    inputManager.addKey(KEY_DOWN);

    inputManager.addListener(new upListener());
    inputManager.addListener(new downListener());
    inputManager.addListener(new leftListener());
    inputManager.addListener(new rightListener());
}

void Level::draw(void) {
    tileMap->draw();
    // player->draw();
    
}

void Level::update() {
    inputManager.update();
    player->update();
    tileMap->update(player);
}

float Level::getWidth() {
    return tileMap->getWidth() * Global::TILE_SIZE * Global::SCALE_FACTOR;
}

float Level::getHeight() {
    return tileMap->getWidth() * Global::TILE_SIZE * Global::SCALE_FACTOR;
}

std::shared_ptr<Character> Level::getCharacter() {
    return player;
}