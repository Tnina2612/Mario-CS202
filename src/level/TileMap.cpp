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
    if(player->getPos().x <= 0) player->hitBlockLeft(0);
    if(player->getPos().x + player->getRectangle().width >= width * BLOCKSIDE) player->hitBlockRight(width * BLOCKSIDE);
    const Rectangle& charRec = player->getRectangle();
    player->setOnGround(false);
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(tiles[i][j] == nullptr) continue;
            const Rectangle& blockRec = tiles[i][j]->getRectangle();
            if(player->getRectangle().y + player->getRectangle().height == blockRec.y) {
                player->setOnGround(true);
            }
            if(CheckCollisionRecs(charRec, blockRec)) {
                float overlapX = min(charRec.x + charRec.width, blockRec.x + blockRec.width) - max(charRec.x, blockRec.x);
                float overlapY = min(charRec.y + charRec.height, blockRec.y + blockRec.height) - max(charRec.y, blockRec.y);
                if(overlapX < overlapY) {
                    if(charRec.x < blockRec.x) {
                        cout << "Player collides right\n";
                        player->hitBlockRight(blockRec.x);
                    } else {
                        cout << "Player collides left\n";
                        player->hitBlockLeft(blockRec.x + blockRec.width);
                    }
                } else {
                    if(charRec.y < blockRec.y) {
                        cout << "Player collides down\n";
                        player->hitBlockBottom(blockRec.y);
                    } else {
                        cout << "Player collides up\n";
                        player->hitBlockTop(blockRec.y + blockRec.height);
                    }
                }
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