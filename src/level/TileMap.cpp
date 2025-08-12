#include<level/TileMap.hpp>

TileMap::TileMap(std::string filename) {
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
            string blockName;
            inp >> blockName;

            Vector2 pos = Vector2{j * BLOCKSIDE, i * BLOCKSIDE};
            if(blockName.find("coin") == 0) {
                tiles[i][j] = make_shared<Block>(pos, 0, "", "question", blockName);
            } else if(blockName.find("brick") == 0) {
                tiles[i][j] = make_shared<Block>(pos, 0, "", "normal", blockName);
            } else if(blockName != "A") {
                tiles[i][j] = make_shared<Block>(pos, 0, "", "solid", blockName);
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
        // cout << "DEBUG IS ON\n";
        for(const Rectangle& block : debugBlocks) {
            DrawRectangleRec(block, Color{100, 255, 100, 50});
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
    if(player->getPos().y >= Global::ORIGINAL_HEIGHT) player->die();
    
    const Rectangle& charRec = player->getRectangle();
    player->resetAttributes();
    float deltaTime = GetFrameTime();
    Rectangle nextFrame = {charRec.x, charRec.y + player->getVeclocityY() * deltaTime, charRec.width, charRec.height};

    std::vector<std::pair<int, int>> nearbyCells = cellsToCheck(nextFrame);

    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width ||
            tiles[i][j] == nullptr) continue;
        const Rectangle& blockRec = tiles[i][j]->getDrawRec();
        if(CheckCollisionRecs(nextFrame, blockRec)) {
            if(nextFrame.y <= blockRec.y) {
                player->hitBlockBottom(blockRec.y);
            } else {
                player->hitBlockTop(blockRec.y + blockRec.height);
                tiles[i][j]->onHit({}, *player);
            }
            nextFrame.y = charRec.y;
        }
    }
    nextFrame.x = charRec.x + player->getVeclocityX() * deltaTime;
    nearbyCells = cellsToCheck(nextFrame);
    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width ||
            tiles[i][j] == nullptr || tiles[i][j]->getStateName() == "Break") continue;
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
    float deltaTime = GetFrameTime();

    // if(!enemy->getOnGround()) {
    //     enemy->applyGravity(deltaTime);
    // }
    enemy->applyGravity(deltaTime);
    enemy->setOnGround(false);
    Rectangle enemyRec = enemy->getHitBox();
    Vector2 dx = enemy->getMovementStrategy()->Execute(enemy->getEnemyData(), deltaTime);
    Rectangle nextFrame = {enemyRec.x, enemyRec.y + dx.y, enemyRec.width, enemyRec.height};
    Rectangle result = {enemyRec.x, enemyRec.y + dx.y + enemyRec.height, enemyRec.width, enemyRec.height};
    

    if(!enemy->isAlive()) {
        enemy->setPos({nextFrame.x, nextFrame.y + nextFrame.height});
        enemy->update(deltaTime);
        return;
    }

    // checking collision on Oy 
    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width ||
            tiles[i][j] == nullptr) continue;
        const Rectangle& blockRec = tiles[i][j]->getDrawRec();

        if(CheckCollisionRecs(nextFrame, blockRec)) 
        {
            if(nextFrame.y <= blockRec.y) {
                result.y = blockRec.y;
                enemy->setOnGround(true);
                enemy->setVelocityY(enemy->getRestVelocity());
            } else {
                enemy->setVelocityY(enemy->getVelocity().y * -1.0f);
            }
            nextFrame.y = enemyRec.y;
            break;
        } 
    }

    //checking collision on Ox
    nextFrame.x = enemyRec.x + dx.x;
    bool okee = false;
    for(std::pair<int, int> pii : nearbyCells) {
        int i = pii.first, j = pii.second;
        if(i < 0 || i >= height || j < 0 || j >= width ||
            tiles[i][j] == nullptr) continue;
        okee = true;
        const Rectangle& blockRec = tiles[i][j]->getDrawRec();

        if(CheckCollisionRecs(nextFrame, blockRec) && enemy->getOnGround()) {
            if(nextFrame.x <= blockRec.x) {
                enemy->hitBlockLeft();
            } else {
                enemy->hitBlockRight();
            }
            nextFrame.x = enemyRec.x;
            break;
        } 
    }

    if(!okee && enemy->getOnGround()) {
        nextFrame.x -= dx.x;
    } 
    result.x = nextFrame.x;

    enemy->setPos({result.x, result.y});
    enemy->update(deltaTime);
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
    out << height << " " << width << "\n";
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(tiles[i][j] == nullptr) {
                out << "A ";
            }
            else {
                out << tiles[i][j]->getBlockName() << " ";
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