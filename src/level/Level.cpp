#include "level/Level.hpp"

Level::Level(void) {
    std::cout << "Level construtor\n";
    tileMap = std::make_shared<TileMap>("./world-maps/1-1-ground.txt");
    std::cout << "End Level constructor\n";
}

void Level::draw(void) {
    tileMap->draw();
}