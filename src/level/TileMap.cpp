#include "level/TileMap.hpp"

TileMap::TileMap(std::string filename) {
    std::ifstream inp(filename);
    inp >> height >> width;
    tiles.resize(height);
    for(int i = 0; i < height; i++) {
        tiles[i].resize(width);
    }
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            string blockType;
            inp >> blockType;
            if(blockType != "A") {
                float posX = j * BLOCKSIDE;
                float posY = i * BLOCKSIDE;
                tiles[i][j] = make_shared<Block>(Vector2{posX, posY}, tileFactory.getBlockFlyweight(blockType));
            } else {
                tiles[i][j].reset();
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

void TileMap::update(std::shared_ptr<Character> player) {
    if(player->getPos().x <= 0) player->hitBlockLeft();
    if(player->getPos().x + player->getRectangle().width >= width * BLOCKSIDE) player->hitBlockRight();
    const Rectangle& charRec = Rectangle{player->getPos().x, player->getPos().y, 16.f, 32.f};//player->getRectangle();
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(tiles[i][j] == nullptr) continue;
            const Rectangle& blockRec = tiles[i][j]->getRectangle();

            // Player collisions on ground
            if(charRec.y + charRec.height == blockRec.y &&
               blockRec.x <= charRec.x + charRec.width &&
               charRec.x <= blockRec.x + blockRec.width) {
                player->hitBlockBottom();
            } 
            // Player head-bumps a block
            else if(charRec.y == blockRec.y + blockRec.height &&
                blockRec.x <= charRec.x + charRec.width && 
                charRec.x <= blockRec.x + blockRec.width) {
                player->hitBlockTop();
                if(player->getCharacterState() == 0) {
                    tiles[i][j]->jiggle();
                }
                else {
                    if(tiles[i][j]->breakBrick()) {
                        tiles[i][j].reset(); // i.e. blockTiles[i][j] = nullptr;
                    }
                }
            }
            // Player collisions left
            else if(charRec.x == blockRec.x + blockRec.width &&
            blockRec.y <= charRec.y + charRec.height &&
            charRec.y <= blockRec.y + blockRec.height) {
                player->hitBlockLeft();
            }
            // Player collision right
            else if(charRec.x + charRec.width == blockRec.x &&
            blockRec.y <= charRec.y + charRec.height &&
            charRec.y <= blockRec.y + blockRec.height) {
                player->hitBlockRight();
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