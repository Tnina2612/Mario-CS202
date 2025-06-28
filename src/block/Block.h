#pragma once
#include "raylib.h"

class Block {
protected:
    Vector2 position;

public:
    Block(float x = 0, float y = 0) : position({ x, y }) {}
    virtual ~Block() = default;

    virtual void Draw() = 0;
    virtual Block* Clone() const = 0;

    void SetPos(float x, float y) { position = { x, y }; }
    Vector2 GetPos() const { return position; }
};
