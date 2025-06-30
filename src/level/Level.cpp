#include "level/Level.hpp"

Level::Level(void) {
    tileMap = std::make_shared<TileMap>("1-1-ground.txt");
}

void Level::draw(void) {
    tileMap->draw();
}