#pragma once
#include "../entities/Character.hpp"
#include <raylib.h>
#include <string>
#include <vector>
#include "Item/Item.h"

class BlockState
{
protected:
    const Vector2 rec_ = Vector2{16.f, 16.f};
public:
    virtual ~BlockState() = default;
    virtual void draw_() = 0;
    virtual void update_() = 0;
    virtual void onHit(Character &character) = 0;
    virtual bool getJiggle() = 0;
    virtual bool getIsDelete() const;
    virtual std::string getStateName() const = 0;
    virtual Rectangle getDrawRec() const = 0;
};