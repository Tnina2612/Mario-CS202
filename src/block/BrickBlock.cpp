// BrickBlock.cpp
#include "BrickBlock.h"

Texture2D BrickBlock::texture = {};

BrickBlock::BrickBlock(float x, float y) : Block(x, y) {}

void BrickBlock::Draw() {
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}

Block* BrickBlock::Clone() const {
    return new BrickBlock(*this);
}

void BrickBlock::LoadTexture() {
    texture = LoadTexture("assets/brick.png");
}

void BrickBlock::UnloadTexture() {
    UnloadTexture(texture);
}
