// QuestionBlock.cpp
#include "QuestionBlock.h"

Texture2D QuestionBlock::texture = {};

QuestionBlock::QuestionBlock(float x, float y) : Block(x, y) {}

void QuestionBlock::Draw() {
    DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), WHITE);
}

Block* QuestionBlock::Clone() const {
    return new QuestionBlock(*this);
}

void QuestionBlock::LoadTexture() {
    texture = LoadTexture("assets/question.png");
}

void QuestionBlock::UnloadTexture() {
    UnloadTexture(texture);
}
