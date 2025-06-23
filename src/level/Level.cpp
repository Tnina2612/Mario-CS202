#include "level/Level.hpp"

Level_1_1_Ground::Level_1_1_Ground(void) : map(15, 48) {
    map.loadFromText("./world-maps/1-1-ground.txt");
}

void Level_1_1_Ground::draw(void) {
    ClearBackground(SKYBLUE);
    map.draw();
}