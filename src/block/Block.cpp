// BlockFactory.cpp
#include <block/Block.h>
#include "core/Variables.hpp"

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