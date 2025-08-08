#pragma once
#include "Item.h"
#include <vector>
#include "raylib.h"
#include <entities/Character.hpp>

class Coin : public Item
{
private:
    std::vector<Rectangle> m_rec;

public:
    Coin(Vector2 pos);
    void update() override;
    void appear() override;
    void activate(Character& character) override;
    bool canMove() const override;
};