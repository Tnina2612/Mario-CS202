#pragma once
#include "Item.h"

enum StateMushroom
{
    super_ = 0,
    one_up,
    posion_
};

class Mushroom : public Item
{
private:
    StateMushroom state_;
    bool direct_, fall_, isAppear, jump_;
    Vector2 velocity_;
    Vector2 previousFramePos;
    const float mushroomIniVelo = 300.0f;
    Vector2 beforePos_;
    const int scoreOneUpSuper = 1000;

public:
    Mushroom(Vector2 pos, StateMushroom state);
    void update() override;
    void activate(Character &character) override;
    void fall();
    void move();
    void jump();
    void beDelete();
    void appear() override;
    void checkFall() override;
    void checkOnGround() override;
    void checkChangeDirect() override;
    void checkJump();
    Vector2 getPreviousFramePos() override;
    bool getDirect() const;
    bool canMove() const override;
};