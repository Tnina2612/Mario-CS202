// InvisibleBlock.h
#pragma once
#include "Block.h"

class InvisibleBlock : public Block {
private:
    static Texture2D texture;

public:
    InvisibleBlock(float x = 0, float y = 0);
    void Draw() override;
    Block* Clone() const override;

    static void LoadTexture();
    static void UnloadTexture();
};
