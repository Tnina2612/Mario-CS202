#include "level/TileMap.hpp"

TileMap::TileMap(std::string filename) {
    std::ifstream inp(filename);

    inp >> height >> width;

    tiles.resize(height);
    for(int i = 0; i < height; i++) tiles[i].resize(width);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int posX = BLOCKSIDE * j;
            int posY = BLOCKSIDE * i;
            std::string type;
            inp >> type;
            
            if(type != "A") {
                tiles[i][j] = std::make_shared<Block>(Vector2{(float)posX, (float)posY}, blockFlyweightFactory.getBlockFlyweight(type));
            }
        }
    }

    inp.close();
}

void TileMap::draw(void) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(tiles[i][j] != nullptr) {
                tiles[i][j]->Draw();
            }
        }
    }
}