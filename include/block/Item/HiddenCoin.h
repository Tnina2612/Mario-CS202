#pragma once
#include "Item.h"

class HiddenCoin : public Item
{
private:
    std::vector<Rectangle> m_rec;
    const float pushHeight = 500.0f;

    Vector2 velocity_;
    Vector2 before_pos_;

    float spriteInterval;

public:
    HiddenCoin(Vector2 pos);

    void update() override;
    void appear() override;
    void activate(Character&character) override;
    bool canMove() const override;
};
