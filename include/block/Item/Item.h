#pragma once
#include "../include/entities/Character.hpp"
#include "../assets/images/Coordinate.h"
#include <entities/Animation.hpp>
#include <raylib.h>
#include <vector>
#include <memory>
#include<iostream>
#include <string>
#include <fstream>
#include <stdexcept>

const float MushroomAndStarSpeed = 80.0f;
const float appearAnimation = 0.75f;
const float tileSize = 16.0f;

class Item
{
private:
    static Texture2D itemTexture;
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
    // virtual Vector2 getPreviousFramePos();
    Rectangle getSourceRec() const;
    Rectangle getDrawRec() const;
    bool isAppearAnimation() const;
    bool isDelete() const;
    virtual bool canMove() const = 0;

    virtual void checkFall() {}
    virtual void checkOnGround() {}
    virtual void checkChangeDirect() {}
    virtual std::string getType() const = 0;
    virtual Vector2 getVelocity() const = 0;
    virtual void saveToFile(std::ofstream& out) const;
    virtual shared_ptr<Item> clone() const = 0;

    static std::shared_ptr<Item> stringToItem(std::string itemData, float x, float y);
    static std::vector<std::shared_ptr<Item>> stringToVectorItem(std::string itemData, float x, float y);
};
