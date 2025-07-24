// BlockFactory.cpp
#include<block/Block.h>
#include<Variables.h>

// Block Flyweight
BlockFlyweight::BlockFlyweight(const char* dir) {
    texture = LoadTexture(dir);
}

void BlockFlyweight::Draw(int posX, int posY) {
    DrawTexture(texture, posX, posY, WHITE);
}

BlockFlyweight::~BlockFlyweight(void) {
    UnloadTexture(texture);
}

// Block
Block::Block(Vector2 position, std::shared_ptr<BlockFlyweight> flyweight) : position(position), flyweight(flyweight) {}

void Block::Draw(void) {
    flyweight->Draw(position.x, position.y);
}

// Block Flyweight Factory
std::shared_ptr<BlockFlyweight> BlockFlyweightFactory::getBlockFlyweight(const std::string& type) {
    if(flyweights.find(type) == flyweights.end()) {
        std::string path = "./assets/images/levels/";
        if(LevelVar::ThemeID == LevelVar::Castle) path += "castle/";
        else if(LevelVar::ThemeID == LevelVar::Mushrooms) path += "mushrooms/";
        else if(LevelVar::ThemeID == LevelVar::Overworld) path += "overworld/";
        else if(LevelVar::ThemeID == LevelVar::Snow) path += "snow/";
        else if(LevelVar::ThemeID == LevelVar::Underground) path += "underground/";
        else if(LevelVar::ThemeID == LevelVar::Underwater) path += "underwater/";
        path += type + ".png";
        flyweights[type] = std::make_shared<BlockFlyweight>(path.c_str());
    }
    return flyweights[type];
}

Rectangle Block::getRectangle() const {
    return Rectangle{ position.x, position.y, 16, 16 };
}


Rectangle BrickBlock::getRectangle() const {
    return Rectangle{ position.x, position.y + jiggleOffset, 16, 16 };
}

void BrickBlock::jiggle() {
    if (jiggleTime <= 0.0f) {
        jiggleTime = 0.2f;
    }
}

bool BrickBlock::breakBrick() {
    if (!isBroken) {
        isBroken = true;
        return true;
    }
    return false;
}

void BrickBlock::update(float deltaTime) {
    if (jiggleTime > 0.0f) {
        jiggleTime -= deltaTime;
        jiggleOffset = -4.0f * sinf((0.2f - jiggleTime) * 20.0f);
        if (jiggleTime <= 0.0f) {
            jiggleOffset = 0.0f;
        }
    }
}

void BrickBlock::Draw() {
    if (isBroken) return;
    flyweight->Draw(position.x, position.y + jiggleOffset);
}

Rectangle QuestionBlock::getRectangle() const {
    return Rectangle{ position.x, position.y + jiggleOffset, 16, 16 };
}

void QuestionBlock::jiggle() {
    if (jiggleTime <= 0.0f && !isUsed) {
        jiggleTime = 0.2f;
        isUsed = true; 
    }
}

bool QuestionBlock::breakBrick() {
    return false;
}

void QuestionBlock::update(float deltaTime) {
    if (jiggleTime > 0.0f) {
        jiggleTime -= deltaTime;
        jiggleOffset = -4.0f * sinf((0.2f - jiggleTime) * 20.0f);
        if (jiggleTime <= 0.0f) {
            jiggleOffset = 0.0f;
        }
    }
}

void QuestionBlock::Draw() {
    flyweight->Draw(position.x, position.y + jiggleOffset);
}

Rectangle GroundBlock::getRectangle() const {
    return Rectangle{ position.x, position.y, 16, 16 };
}