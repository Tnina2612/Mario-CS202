// BlockFactory.cpp
#include "BlockFactory.h"
#include "BrickBlock.h"
#include "QuestionBlock.h"
#include "InvisibleBlock.h"

std::map<std::string, Block*> BlockFactory::blockPrototypes;

void BlockFactory::Init() {
    BrickBlock::LoadTexture();
    QuestionBlock::LoadTexture();
    InvisibleBlock::LoadTexture();

    blockPrototypes["Brick"] = new BrickBlock();
    blockPrototypes["Question"] = new QuestionBlock();
    blockPrototypes["Invisible"] = new InvisibleBlock();
}

Block* BlockFactory::CreateBlock(const std::string& type, float x, float y) {
    if (blockPrototypes.find(type) == blockPrototypes.end()) return nullptr;
    Block* block = blockPrototypes[type]->Clone();
    block->SetPos(x, y);
    return block;
}

void BlockFactory::CleanUp() {
    for (auto& pair : blockPrototypes)
        delete pair.second;
    blockPrototypes.clear();

    BrickBlock::UnloadTexture();
    QuestionBlock::UnloadTexture();
    InvisibleBlock::UnloadTexture();
}
