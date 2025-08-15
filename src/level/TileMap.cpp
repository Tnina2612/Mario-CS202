#include<cmath>
#include<level/TileMap.hpp>
#include<level/Level.hpp>
#include<iomanip>

TileMap::TileMap(std::string filename, SubLevel* subLevel) : subLevel(subLevel) {
    std::ifstream inp(filename);
    if(inp.is_open() == false) {
        throw runtime_error("Cannot open file " + filename);
    }
    inp >> height >> width;
    tiles.resize(height);
    for(int i = 0; i < height; i++) {
        tiles[i].resize(width);
    }
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            string blockData;
            inp >> blockData;
            Vector2 pos = Vector2{j * BLOCKSIDE, i * BLOCKSIDE};
            if(blockData != "A") {
                tiles[i][j] = make_shared<Block>(pos, blockData);
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
                tiles[i][j]->draw_();
            }
        }
    }

    if(debug) {
        for(const Rectangle& block : debugPlayerBlocks) {
            DrawRectangleRec(block, Color{100, 255, 100, 50});
        }
        for(const Rectangle& block : debugItemBlocks) {
            DrawRectangleRec(block, Color{100, 100, 255, 50});
        }
    }
}

void TileMap::updateBlocks() {
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(tiles[i][j] == nullptr) continue;
            tiles[i][j]->update_();
            if(tiles[i][j]->getIsDelete() == true) {
                tiles[i][j].reset();
            }
        }
    }
}

void TileMap::update(Character* player) {
    // if(player->getPos().y >= Global::ORIGINAL_HEIGHT + 64.0f) player->die();
    
    const Rectangle& charRec = player->getRectangle();
    player->resetAttributes();
    float deltaTime = GetFrameTime();
    Rectangle nextFrame = {charRec.x, charRec.y + player->getVeclocityY() * deltaTime, charRec.width, charRec.height};
    
    std::vector<std::pair<int, int>> nearbyCells = cellsToCheck(nextFrame);

    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width || tiles[i][j] == nullptr || tiles[i][j]->getBlockName().find("coin") != 0) {
            continue;
        }   
        if(CheckCollisionRecs({charRec.x + player->getVeclocityX() * deltaTime, charRec.y + player->getVeclocityY() * deltaTime, charRec.width, charRec.height}, 
                            tiles[i][j]->getDrawRec())) {
            // player->addCoin();
            tiles[i][j].reset();
        }
    }

    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width || tiles[i][j] == nullptr || tiles[i][j]->getStateName() != "Invisible") {
            continue;
        }
        if(CheckCollisionRecs(nextFrame, tiles[i][j]->getDrawRec()) && nextFrame.y >= tiles[i][j]->getDrawRec().y) {
            tiles[i][j]->onHit(*player);
        }
    }

    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(isCollidableTile(i, j) == false) continue;
        const Rectangle& blockRec = tiles[i][j]->getDrawRec();
        if(CheckCollisionRecs(nextFrame, blockRec)) {
            if(nextFrame.y <= blockRec.y) {
                player->hitBlockBottom(blockRec.y);
            } else {
                player->hitBlockTop(blockRec.y + blockRec.height);
                tiles[i][j]->onHit(*player);
                std::shared_ptr<Item> item = tiles[i][j]->popAppearingItem();
                if(item != nullptr) {
                    subLevel->itemManager.addItem(item);
                }
            }
            nextFrame.y = charRec.y;
        }
    }
    nextFrame.x = charRec.x + player->getVeclocityX() * deltaTime;
    nearbyCells = cellsToCheck(nextFrame);
    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(isCollidableTile(i, j) == false) continue;
        const Rectangle& blockRec = tiles[i][j]->getDrawRec();
        if(CheckCollisionRecs(nextFrame, blockRec)) {
            if(nextFrame.x <= blockRec.x) {
                player->hitBlockRight(blockRec.x);
            } else {
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

    // Debug
    debugPlayerBlocks.clear();
    for(std::pair<int, int> pos : nearbyCells) {
        debugPlayerBlocks.push_back(Rectangle{1.f * pos.second * BLOCKSIDE, 
        1.f * pos.first * BLOCKSIDE, BLOCKSIDE, BLOCKSIDE});
    }

    if(IsKeyPressed(KEY_Q)) {
        debug = debug ^ true;
    }
}

void TileMap::update(std::shared_ptr<Enemy> enemy) {
    std::vector<std::pair<int, int>> nearbyCells = cellsToCheck(enemy->getHitBox());
    float deltaTime = GetFrameTime();

    enemy->applyGravity(deltaTime);
    Rectangle enemyRec = enemy->getHitBox();
    Vector2 movement = enemy->getMovementStrategy()->Execute(enemy->getEnemyData(), deltaTime);
    Rectangle nextFrame = {enemyRec.x, enemyRec.y + movement.y, enemyRec.width, enemyRec.height};
    
    if(!enemy->isAlive() ) {
        enemy->setPos({nextFrame.x, nextFrame.y + nextFrame.height});
        enemy->update(deltaTime);
        return;
    }

    if(!enemy->physics()) {
        enemy->setPos({nextFrame.x, nextFrame.y + nextFrame.height});
        enemy->update(deltaTime);
        return;
    }

    if (enemy->preventFalling()) {
        if(preventFalling(enemy, movement)) {
            return;
        }
    }
    // checking collision on Oy 
    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(isCollidableTile(i, j) == false) continue;
        const Rectangle& blockRec = tiles[i][j]->getDrawRec();

        if(CheckCollisionRecs(nextFrame, blockRec)) 
        {
            if(nextFrame.y <= blockRec.y) {
                // result.y = blockRec.y;
                enemy->setOnGround(true);
                enemy->setVelocityY(enemy->getRestVelocity());
                nextFrame.y = blockRec.y - enemyRec.height;
            } else {
                enemy->setVelocityY(enemy->getVelocity().y * -1.0f);
                nextFrame.y = blockRec.y + blockRec.height;
            }
            // nextFrame.y = enemyRec.y;
            break;
        } 
    }
    enemyRec = nextFrame;

    nextFrame = enemyRec;
    nextFrame.x += movement.x;

    //checking collision on Ox

    //nextFrame.x = enemyRec.x + movement.x;

    // nextFrame.y = result.y;

    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(isCollidableTile(i, j) == false) continue;

        const Rectangle& blockRec = tiles[i][j]->getDrawRec();

        if(CheckCollisionRecs(nextFrame, blockRec)) {
            if(nextFrame.x <= blockRec.x) {
                nextFrame.x = blockRec.x - enemyRec.width;
                enemy->hitBlockLeft();
            } else {
                nextFrame.x = blockRec.x + blockRec.width;
                enemy->hitBlockRight();
            }
            // nextFrame.x = enemyRec.x;
            break;
        } 
    }

    enemy->setPos({nextFrame.x, nextFrame.y + nextFrame.height});
}

void TileMap::update(std::shared_ptr<Item> item) {
    if(item->getType().find("mushroom") == std::string::npos) {
        return;
    }

    Rectangle itemRec = item->getDrawRec();
    Vector2 movement = item->getVelocity();
    Rectangle nextFrame = {itemRec.x, itemRec.y + movement.y * GetFrameTime(), itemRec.width, itemRec.height};
    item->checkFall();
    std::vector<std::pair<int, int>> nearbyCells = cellsToCheck(nextFrame);
    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(isCollidableTile(i, j) == false) continue;
        if(CheckCollisionRecs(nextFrame, tiles[i][j]->getDrawRec())) {
            if(nextFrame.y <= tiles[i][j]->getDrawRec().y) {
                item->checkOnGround();
            } else {
                item->checkFall();
            }
            nextFrame.y = itemRec.y;
        }
    }
    nearbyCells = cellsToCheck(nextFrame);
    nextFrame.x += movement.x * GetFrameTime();
    bool changeDirection = false;
    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(isCollidableTile(i, j) == false) continue;
        if(CheckCollisionRecs(nextFrame, tiles[i][j]->getDrawRec())) {
            if(nextFrame.x <= tiles[i][j]->getDrawRec().x) {
                if(movement.x > 0) {
                    changeDirection = true;
                }
            } else {
                if(movement.x < 0) {
                    changeDirection = true;
                }
            }
            nextFrame.x = itemRec.x;
        }
    }

    if(changeDirection) {
        item->checkChangeDirect();
    }

    itemRec = nextFrame;
    item->setPos({itemRec.x + itemRec.width / 2.f, itemRec.y + nextFrame.height});

    // Debug
    debugItemBlocks.clear();
    for(std::pair<int, int> pos : nearbyCells) {
        debugItemBlocks.push_back(Rectangle{1.f * pos.second * BLOCKSIDE, 
        1.f * pos.first * BLOCKSIDE, BLOCKSIDE, BLOCKSIDE});
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

void TileMap::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if(!out.is_open()) {
        throw std::runtime_error("Cannot open file " + filename);
    }
    out << left << setw(20) << height << left << setw(20) << width << "\n";
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(tiles[i][j] == nullptr) {
                out << left << setw(20) << "A";
            }
            else {
                out << left << setw(20) << tiles[i][j]->getBlockName();
            }
        }
        out << "\n";
    }
    out.close();
}

float TileMap::getWidth() {
    return width;
}

float TileMap::getHeight() {
    return height;
}

bool TileMap::isCollidableTile(int i, int j) {
    if(i < 0 || i >= height || j < 0 || j >= width || tiles[i][j] == nullptr) {
        return false;
    }
    std::string stateName = tiles[i][j]->getStateName();
    return stateName != "Invisible" && stateName != "Break";
}

bool TileMap::preventFalling(std::shared_ptr<Enemy> enemy, Vector2& movement) {
    Rectangle enemyRec = enemy->getHitBox();

    float nextX = enemyRec.x + movement.x;
    float footY = enemyRec.y + enemyRec.height + 1;

    int tileBelowRow = (int) (footY / BLOCKSIDE);
    int tileBelowCol = (int) ((nextX + enemyRec.width / 2.f) / BLOCKSIDE);

    if (tileBelowRow < 0 || tileBelowRow >= height || tileBelowCol < 0 || tileBelowCol >= width) {
        enemy->changeDirection();
        movement.x = 0;
        return true;
    }

    if (tiles[tileBelowRow][tileBelowCol] == nullptr) {
        enemy->changeDirection();   
        movement.x = 0;
        return true;
    }

    return false;
}

void TileMap::update(std::shared_ptr<MovingPlatform> platform, Character* player) {
    const Rectangle& charRec = player->getRectangle();
    const Rectangle& platformRec = platform->getRect();
    
    if(CheckCollisionRecs(charRec, platformRec)) {
        if(charRec.y <= platformRec.y) {
            player->setPosition(charRec.x, platformRec.y);
            player->hitBlockBottom(platformRec.y);
        }
        else if(charRec.y > platformRec.y)  {
            player->setPosition(charRec.x, platformRec.y + charRec.height + platformRec.height);
            player->hitBlockTop(platformRec.y + platformRec.height);
        }
    }
}