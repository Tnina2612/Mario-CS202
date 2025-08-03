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
                if(blockType == "G2") {
                    tiles[i][j] = make_shared<BrickBlock>(Vector2{posX, posY}, tileFactory.getBlockFlyweight("G2"));
                } else if(blockType == "C1") {
                    tiles[i][j] = make_shared<QuestionBlock>(Vector2{posX, posY}, tileFactory.getBlockFlyweight("C1"));
                } else {
                    tiles[i][j] = make_shared<Block>(Vector2{posX, posY}, tileFactory.getBlockFlyweight(blockType));
                }
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
    // cout << "veclocity Y" << player->getVeclocityY();
    if(player->getPos().x + player->getRectangle().width >= width * BLOCKSIDE) {
        player->hitBlockRight(width * BLOCKSIDE);
        // player->setPosition()
    }
    const Rectangle& charRec = player->getRectangle();
    player->resetAttributes();
    float deltaTime = GetFrameTime();
    Rectangle nextFrame = {charRec.x, charRec.y + player->getVeclocityY() * deltaTime, charRec.width, charRec.height};


    std::vector<std::pair<int, int>> nearbyCells = cellsToCheck(nextFrame);

    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width ||
            tiles[i][j] == nullptr) continue;
        const Rectangle& blockRec = tiles[i][j]->getRectangle();
        if(CheckCollisionRecs(nextFrame, blockRec)) {
            if(nextFrame.y <= blockRec.y) {
                // cout << "Player collides down\n";
                player->hitBlockBottom(blockRec.y);
            } else {
                // cout << "Player collides up\n";
                player->hitBlockTop(blockRec.y + blockRec.height);
            }
            nextFrame.y = charRec.y;
        }
    }
    nextFrame.x = charRec.x + player->getVeclocityX() * deltaTime;
    nearbyCells = cellsToCheck(nextFrame);
    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width ||
            tiles[i][j] == nullptr) continue;
        const Rectangle& blockRec = tiles[i][j]->getRectangle();
        if(CheckCollisionRecs(nextFrame, blockRec)) {
            if(nextFrame.x <= blockRec.x) {
                cout << "Player collides right\n";
                player->hitBlockRight(blockRec.x);
            } else {
                cout << "Player collides left\n";
                player->hitBlockLeft(blockRec.x + blockRec.width);
            }
            nextFrame.x = charRec.x;
        }
    }
    if(nextFrame.x <= 0) {
        nextFrame.x = charRec.x;
    }
    player->setPosition(nextFrame.x, nextFrame.y + charRec.height);
    if(!player->getOnGround()) {
        player->setVeclocityY(player->getVeclocityY() + player->getGravity() * deltaTime);
    }

    player->update();

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

void TileMap::update(std::shared_ptr<Enemy> enemy) {
    std::vector<std::pair<int, int>> nearbyCells = cellsToCheck(enemy->getHitBox());
    // enemy->update();
    for(std::pair<int, int> pii : nearbyCells) {
        // enemy->collisionTile(tiles[pii.first][pii.second]);
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