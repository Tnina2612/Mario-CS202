#pragma once
#include "Character.hpp"
#include "Coordinate.h"


const float MushroomAndStarSpeed = 120.0f;
const float appearAnimation = 0.75f;
// const float Tile_Size = 16.0f * scale_screen;

class Item
{
private:
    Texture2D item_;

protected:
    Vector2 pos_;
    Rectangle rec_;
    float frame_;
    int type_;
    bool appearAnimation;
    bool isDelete;

public:
    Item(Vector2 pos);

    void draw_();
    virtual void update_() = 0;
    virtual void appear_() = 0;
    virtual void activate_(Character &character) = 0;

    Vector2 getPos() const;
    void setPos(Vector2 pos);
    virtual Vector2 getPreviousFramePos() {}
    Rectangle getSourceRec() const;
    Rectangle getDrawRec() const;
    bool isAppearAnimation() const;
    bool getIsDelete() const;
    virtual bool canMove() const = 0;

    virtual void checkFall() {}
    virtual void checkOnGround() {}
    virtual void checkChangeDirect() {}
};
