#pragma once
#include "../Item/Item.h"

class Star : public Item
{
private:
    bool direct_, isAppear;
    Vector2 beforePos;
    Vector2 previousFramePos;
    Vector2 velocity_; 
    const float starIniVelo = 300.0f;
    const int scoreStar = 1000;

public:
    Star(Vector2 pos);

    void checkOnGround() override;
    void checkChangeDirect() override;

    void fall(float dt);
    void move(float dt);
    void beDelete();

    void appear() override;
    void update() override;
    void activate(Character& character) override;

    // Vector2 getPreviousFramePos() override;
    bool getDirect() const;
    bool canMove() const override;
    std::string getType() const override;
};
