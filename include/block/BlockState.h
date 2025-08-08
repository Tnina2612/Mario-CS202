#pragma once
#include "../entities/Character.hpp"
#include <raylib.h>
#include <string>
#include <vector>
#include "Item/Item.h"

class BlockState
{
protected:
    Rectangle rec_;

public:
    virtual ~BlockState() = default;
    virtual void draw_() = 0;
    virtual void update_() = 0;
    virtual void onHit(std::vector<Item *> &item, Character &character) = 0;
    virtual bool getJiggle() = 0;
    virtual bool getIsDelete() const;
    Rectangle getSourceRec() const;
    virtual Rectangle getDrawRec() const = 0;
};
