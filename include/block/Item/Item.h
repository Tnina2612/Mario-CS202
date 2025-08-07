#pragma once
#include "Character.hpp"
#include "Coordinate.h"
#include <raylib.h>
#include <vector>

const float MushroomAndStarSpeed = 120.0f;
const float appearAnimation = 0.75f;
const float tileSize = 16.0f * 3.0f;

class Item
{
private:
    Texture2D itemTexture;
protected:
    Vector2 pos_;
    Rectangle rec_;
    float frame_;
    int type_;
    bool appearAnimation;
    bool isDelete_;

public:
    Item(Vector2 pos);
    virtual ~Item() = default;
    void draw();
    virtual void update() = 0;
    virtual void appear() = 0;
    virtual void activate(Character &character) = 0;

    Vector2 getPos() const;
    void setPos(Vector2 pos);
    virtual Vector2 getPreviousFramePos() {}
    Rectangle getSourceRec() const;
    Rectangle getDrawRec() const;
    bool isAppearAnimation() const;
    bool isDelete() const;
    virtual bool canMove() const = 0;

    virtual void checkFall() {}
    virtual void checkOnGround() {}
    virtual void checkChangeDirect() {}
};
