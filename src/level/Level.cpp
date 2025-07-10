#include "level/Level.hpp"

Level::Level(const std::string& fileName) {
    tileMap = std::make_shared<TileMap>(fileName);
}

void Level::draw(void) {
    tileMap->draw();
}