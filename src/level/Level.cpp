#include "level/Level.hpp"

Level::Level(const std::string& fileName) {
    tileMap = std::make_shared<TileMap>(fileName);
    character = std::make_shared<Mario>();
}

void Level::draw(void) {
    tileMap->draw();
    character->update();
    character->draw();
}