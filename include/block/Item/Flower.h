#pragma once
#include "Item.h"

class Flower : public Item
{
private:
    bool isAppear;
    Vector2 beforePos;
    const int ScoreFlower = 1000;

public:
    Flower(Vector2 pos);
    void update() override;
    void appear() override;
    void activate(Character &character) override;
    bool canMove() const override;
    std::string getType() const override;
};