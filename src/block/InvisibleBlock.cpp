// InvisibleBlock.cpp
#include "InvisibleBlock.h"

Texture2D InvisibleBlock::texture = {};

InvisibleBlock::InvisibleBlock(float x, float y) : Block(x, y) {}

void InvisibleBlock::Draw() {
    // Hoặc dùng DrawRectangleLinesEx(...) nếu không có texture
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}

Block* InvisibleBlock::Clone() const {
    return new InvisibleBlock(*this);
}

void InvisibleBlock::LoadTexture() {
    texture = LoadTexture("assets/invisible.png"); // hoặc placeholder
}

void InvisibleBlock::UnloadTexture() {
    UnloadTexture(texture);
}
