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

    if(debug) {
        // cout << "DEBUG IS ON\n";
        for(const Rectangle& block : debugBlocks) {
            DrawRectangleRec(block, Color{100, 255, 100, 50});
        }
    }
}

void TileMap::update(std::shared_ptr<Character> player) {
    if(player->getPos().x <= 0) player->hitBlockLeft(0);
    if(player->getPos().x + player->getRectangle().width >= width * BLOCKSIDE) player->hitBlockRight(width * BLOCKSIDE);
    const Rectangle& charRec = player->getRectangle();
    player->resetAttributes();
    // cout << "Character rectangle: " << charRec.x << ' ' << charRec.y << ' ' << charRec.x + charRec.width << ' ' << charRec.y + charRec.height << '\n';

    std::vector<std::pair<int, int>> nearbyCells = cellsToCheck(charRec);

    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width ||
            tiles[i][j] == nullptr) continue;
        const Rectangle& blockRec = tiles[i][j]->getRectangle();
        if(charRec.y + charRec.height == blockRec.y && 
            charRec.x + charRec.width > blockRec.x &&
            charRec.x < blockRec.x + blockRec.width) {
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

    // Debug
    debugBlocks.clear();
    for(std::pair<int, int> pos : nearbyCells) {
        debugBlocks.push_back(Rectangle{1.f * pos.second * BLOCKSIDE, 
        1.f * pos.first * BLOCKSIDE, BLOCKSIDE, BLOCKSIDE});
    }

    if(IsKeyPressed(KEY_Q)) {
        debug = debug ^ true;
    }
}

std::vector<std::pair<int, int>> TileMap::cellsToCheck(const Rectangle& rec) {
    Vector2 topLeft = {rec.x, rec.y};
    std::pair<int, int> TL = {topLeft.x / BLOCKSIDE, topLeft.y / BLOCKSIDE};
    Vector2 topRight = {rec.x + rec.width, rec.y};
    std::pair<int, int> TR = {topRight.x / BLOCKSIDE, topRight.y / BLOCKSIDE};
    Vector2 botLeft = {rec.x, rec.y + rec.height};
    std::pair<int, int> BL = {botLeft.x / BLOCKSIDE, botLeft.y / BLOCKSIDE};
    Vector2 botRight = {rec.x + rec.width, rec.y + rec.height};
    std::pair<int, int> BR = {botRight.x / BLOCKSIDE, botRight.y / BLOCKSIDE};

    std::vector<std::pair<int, int>> res;
    res.push_back({TL.second, TL.first});
    res.push_back({TL.second - 1, TL.first});
    res.push_back({TL.second, TL.first - 1});

    res.push_back({TR.second, TR.first});
    res.push_back({TR.second - 1, TR.first});
    res.push_back({TR.second, TR.first + 1});

    res.push_back({BL.second, BL.first});
    res.push_back({BL.second - 1, BL.first});
    res.push_back({BL.second - 1, BL.first - 1});

    res.push_back({BR.second, BR.first});
    res.push_back({BR.second - 1, BR.first});
    res.push_back({BR.second - 1, BR.first + 1});

    return res;
}

float TileMap::getWidth() {
    return width;
}

float TileMap::getHeight() {
    return height;
}