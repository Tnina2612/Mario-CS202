#include "block/Item/Mushroom.h"
#include <iostream>
const float scale_screen = 3.0f;
Mushroom::Mushroom(Vector2 pos, StateMushroom state)
    : Item(pos), state_(state), direct_(1), fall_(false), isAppear(false), jump_(false), beforePos_({pos.x, pos.y})
{
    velocity_ = {0.0f, 0.0f};
    previousFramePos = pos_;

    switch (state_)
    {
    case StateMushroom::super_:
        rec_ = ItemSprite::MUSHROOM_SUPER;
        break;
    case StateMushroom::one_up:
        rec_ = ItemSprite::MUSHROOM_ONE_UP;
        break;
    // case StateMushroom::poison_:
    //     rec_ = ItemSprite::MUSHROOM_POISON;
    //     break;
    default:
        break;
    }
}

void Mushroom::checkFall()
{
    if (!jump_ && !fall_)
    {
        fall_ = true;
        velocity_.y = 0.0f; 
    }
}

void Mushroom::checkOnGround()
{
    fall_ = false;
    jump_ = false;
    velocity_.y = 0.0f;
}

void Mushroom::checkChangeDirect() { 
    direct_ = !direct_; 
}

void Mushroom::checkJump()
{
    jump_ = true;
    fall_ = false;
    velocity_.y = -mushroomIniVelo;
}

void Mushroom::jump()
{
    if (!isAppear || !jump_)
        return;
    float dt = GetFrameTime();
    velocity_.y += 1000.0f * dt;
    velocity_.x = direct_ * MushroomAndStarSpeed * dt;
}

void Mushroom::fall()
{
    if (!isAppear || !fall_)
        return;
    float dt = GetFrameTime();
    velocity_.y += 1000.0f * dt;
    velocity_.x = direct_ * MushroomAndStarSpeed * dt;
}

void Mushroom::move() {
    if (!isAppear || fall_ || jump_)
        return;
    velocity_.x = (direct_ ? 1 : -1) * MushroomAndStarSpeed;
    velocity_.y = 0.0f;
}

void Mushroom::appear()
{
    if (isAppear)
        return;
    pos_.y -= appearAnimation;
    if (pos_.y <= beforePos_.y - tileSize)
    {
        appearAnimation = 0;
        isAppear = true;
        pos_.y = beforePos_.y - tileSize;
        previousFramePos = pos_;
    }
}

void Mushroom::beDelete()
{
    if (pos_.y - rec_.height >= Global::ORIGINAL_HEIGHT) {
        isDelete_ = true;
    }
    if(pos_.x < 0) {
        isDelete_ = true;
    }
}

void Mushroom::update()
{
    previousFramePos = pos_;
    appear();
    move();
    fall();
    jump();
    beDelete();
}

void Mushroom::activate(Character& character)
{
    if (state_ == StateMushroom::super_)
    {
        character.powerUp();
    } else {
        character.addLife();
    }
//     info.UpdateScore(Score_One_Up_Super);

    isDelete_ = true;
}

// Vector2 Mushroom::getPreviousFramePos() { return previousFramePos; }

bool Mushroom::getDirect() const { return direct_; }

bool Mushroom::canMove() const { return true; }

std::string Mushroom::getType() const {
    return "mushroom" + to_string(state_);
}

Vector2 Mushroom::getVelocity() const {
    return velocity_;
}

shared_ptr<Item> Mushroom::clone() const {
    shared_ptr<Item> ret = make_shared<Mushroom>(pos_, state_);
    return ret;
}