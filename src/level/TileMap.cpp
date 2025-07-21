#include "level/TileMap.hpp"

TileMap::TileMap(std::string filename) {
    std::string folder = "./world-maps/";
    std::string backgroundFile = folder + "background-maps/" + filename;
    std::string objectFile = folder + "object-maps/" + filename;

    std::ifstream inp(backgroundFile);
    inp >> height >> width;

    backgroundTiles.resize(height);
    for(int i = 0; i < height; i++) backgroundTiles[i].resize(width);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int posX = BLOCKSIDE * j;
            int posY = BLOCKSIDE * i;
            std::string type;
            inp >> type;

            if(type != "A") {
                backgroundTiles[i][j] = std::make_shared<Block>(Vector2{(float)posX, (float)posY}, blockFlyweightFactory.getBlockFlyweight(type));
            }
        }
    }
    inp.close();

    inp.open(objectFile);
    inp >> height >> width;

    objectTiles.resize(height);
    for(int i = 0; i < height; i++) objectTiles[i].resize(width);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int posX = BLOCKSIDE * j;
            int posY = BLOCKSIDE * i;
            std::string type;
            inp >> type;

            if(type != "A") {
                objectTiles[i][j] = std::make_shared<Block>(Vector2{(float)posX, (float)posY}, blockFlyweightFactory.getBlockFlyweight(type));
            }
        }
    }
    inp.close();
}

void TileMap::draw(void) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(backgroundTiles[i][j] != nullptr) {
                backgroundTiles[i][j]->Draw();
            }
        }
    }

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(objectTiles[i][j] != nullptr) {
                objectTiles[i][j]->Draw();
            }
        }
    }
}

float TileMap::getWidth() {
    return width;
}

float TileMap::getHeight() {
    return height;
}