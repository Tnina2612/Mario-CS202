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

    blockTiles.resize(height);
    for(int i = 0; i < height; i++) blockTiles[i].resize(width);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            int posX = BLOCKSIDE * j;
            int posY = BLOCKSIDE * i;
            std::string type;
            inp >> type;

            if(type != "A") {
                blockTiles[i][j] = std::make_shared<Block>(Vector2{(float)posX, (float)posY}, blockFlyweightFactory.getBlockFlyweight(type));
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
            if(blockTiles[i][j] != nullptr) {
                blockTiles[i][j]->Draw();
            }
        }
    }
}

void TileMap::update(std::shared_ptr<Character> player) {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(blockTiles[i][j] == nullptr) continue;
    //         const Rectangle& charRec = player->getRectangle();
    //         const Rectangle& blockRec = blockTiles[i][j]->getRectangle();

            // Player collisions on ground
    //         if(charRec.y + charRec.height == blockRec.y &&
    //            blockRec.x <= charRec.x + charRec.width &&
    //            charRec.x <= blockRec.x + blockRec.width) {
    //             player->collisionBottom(true);
    //         } 
            // Player head-bumps a block
    //         else if(charRec.y == blockRec.y + blockRec.height &&
    //             blockRec.x <= charRec.x + charRec.width && 
    //             charRec.x <= blockRec.x + blockRec.width) {
    //             player->collisionTop(blockRec);
    //             if(player->isSmall()) {
    //                 blockTiles[i][j]->jiggles();
    //             }
    //             else {
    //                 if(blockTiles[i][j]->break()) {
    //                     blockTiles[i][j].reset(); // i.e. blockTiles[i][j] = nullptr;
    //                 }
    //             }
    //         }
            // Player collisions left
    //         else if(charRec.x == blockRec.x + blockRec.width &&
    //         blockRec.y <= charRec.y + charRec.height &&
    //         charRec.y <= blockRec.y + blockRec.height) {
    //             player->collisionLeft();
    //         }
            // Player collision right
    //         else if(charRec.x + charRec.width == blockRec.x &&
    //         blockRec.y <= charRec.y + charRec.height &&
    //         charRec.y <= blockRec.y + blockRec.height) {
    //             player->collisionRight();
    //         }
        }
    }
}

float TileMap::getWidth() {
    return width;
}

float TileMap::getHeight() {
    return height;
}