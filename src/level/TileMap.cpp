#include "level/TileMap.hpp"

TileMap::TileMap(int height, int width) : height(height), width(width) {
    // tiles.resize(height);
    // for (int i = 0; i < height; ++i) {
    //     tiles[i].resize(width);
    // }
}

void TileMap::loadFromText(std::string dir) {
    std::ifstream inp(dir);
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            std::string type;
            inp >> type;
            if(type == "G1") {
                // Load G1 block
            }
        }
    }
    inp.close();
}

void TileMap::draw(void) {
    // for(int i = 0; i < height; i++) {
    //     for(int j = 0; j < width; j++) {
    //         if(tiles[i][j] != nullptr) {
    //             tiles[i][j]->draw();
    //         }
    //     }
    // }
}