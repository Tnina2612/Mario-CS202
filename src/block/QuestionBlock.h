// QuestionBlock.h
#pragma once
#include "Block.h"

class QuestionBlock : public Block {
private:
    static Texture2D texture;

public:
    QuestionBlock(float x = 0, float y = 0);
    void Draw() override;
    Block* Clone() const override;

    static void LoadTexture();
    static void UnloadTexture();
};
