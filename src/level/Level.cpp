#include "level/Level.hpp"

Level::Level(const std::string& fileName) {
    tileMap = std::make_shared<TileMap>(fileName);
    player = std::make_shared<Mario>();
}

void Level::draw(void) {
    tileMap->draw();
    // player->draw();
    
}

void Level::update() {
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