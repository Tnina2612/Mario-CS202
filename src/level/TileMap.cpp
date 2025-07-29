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
    const Rectangle& charRec = Rectangle{player->getRectangle().x, player->getRectangle().y, 
        player->getRectangle().width, player->getRectangle().height};//player->getRectangle();
    player->setOnGround(false); // Reset on ground status before checking collisions
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(tiles[i][j] == nullptr) {
                continue; // Skip empty tiles
            }
            const Rectangle& blockRec = tiles[i][j]->getRectangle();

            // Player collisions on ground
            if(blockRec.y <= charRec.y + charRec.height && charRec.y <= blockRec.y  &&
               blockRec.x <= charRec.x + charRec.width && charRec.x <= blockRec.x + blockRec.width) {
                player->hitBlockBottom();
            }
            // Player head-bumps a block
            if(charRec.y <= blockRec.y + blockRec.height && blockRec.y <= charRec.y &&
                blockRec.x <= charRec.x + charRec.width && charRec.x <= blockRec.x + blockRec.width) {
                player->hitBlockTop();
                if(player->getCharacterState() == SMALL) {
                    tiles[i][j]->jiggle();
                }
                else {
                    if(tiles[i][j]->breakBrick()) {
                        tiles[i][j].reset(); // i.e. blockTiles[i][j] = nullptr;
                    }
                }
            }
            // Player collisions left
            if(charRec.x <= blockRec.x + blockRec.width && blockRec.x <= charRec.x &&
            blockRec.y <= charRec.y + charRec.height && charRec.y <= blockRec.y + blockRec.height) {
                player->hitBlockLeft();
            }
            // Player collision right
            if(charRec.x + charRec.width >= blockRec.x && charRec.x < blockRec.x &&
            blockRec.y <= charRec.y + charRec.height && charRec.y <= blockRec.y + blockRec.height) {
                cout << "Hit block right" << endl;
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