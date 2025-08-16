#include "block/Item/Star.h"
#include <iostream>
const float scale_screen = 3.0f;
Star::Star(Vector2 pos): Item(pos),direct_(true),isAppear(false),beforePos(pos),velocity_({0.0f, -starIniVelo}),previousFramePos(pos)
{
    rec_ = ItemSprite::STAR[0];
}

void Star::checkOnGround()
{
    if (velocity_.y != -starIniVelo)
    {
        velocity_.y = -starIniVelo;
        beforePos = pos_;
    }
}

void Star::checkChangeDirect()
{
    direct_ = !direct_;
}

void Star::fall(float dt)
{
    if (!isAppear)
        return;

    velocity_.y += 1000.0f * dt;
    pos_.y += velocity_.y * dt;
}

void Star::move(float dt)
{
    if (!isAppear)
        return;

    float speed = MushroomAndStarSpeed * dt;
    if (direct_)
        pos_.x += speed;
    else
        pos_.x -= speed;


}

void Star::appear()
{
    if (isAppear)
        return;

    pos_.y -= appearAnimation;

    if (pos_.y <= beforePos.y - tileSize)
    {
        appearAnimation = false;
        isAppear = true;
        pos_.y = beforePos.y - tileSize;
        beforePos = pos_;
        previousFramePos = pos_;
        // nhảy
        velocity_.y = -starIniVelo;
    }
}

void Star::beDelete()
{
    if (pos_.y - rec_.height >= Global::ORIGINAL_HEIGHT) {
        isDelete_ = true;
    }
    if(pos_.x < 0) {
        isDelete_ = true;
    }
}

void Star::update()
{
    float dt = GetFrameTime();
    previousFramePos = pos_;
    // đổi màu
    const float frameSpeed = 10.0f; 
    frame_ += frameSpeed * dt;
    int frameIndex = static_cast<int>(frame_) % ItemSprite::STAR.size();
    rec_ = ItemSprite::STAR[frameIndex];

    appear();
    move(dt);
    fall(dt);
    beDelete();

    // if (pos_.y + rec_.height * scale_screen >= Global::ORIGINAL_HEIGHT) {
    //     pos_.y = Global::ORIGINAL_HEIGHT - rec_.height* scale_screen;
    //     checkOnGround();
    // }
    if (pos_.y + rec_.height * scale_screen / 2.0f >= Global::ORIGINAL_HEIGHT) {
    pos_.y = Global::ORIGINAL_HEIGHT - rec_.height * scale_screen / 2.0f;
    checkOnGround();
}

    beDelete();
}

void Star::activate(Character &character)
{
//     character.getStar();
//     character.updateScore(Score_Star);
    isDelete_ = true;
}

// Vector2 Star::getPreviousFramePos()
// {
//     return previousFramePos;
// }

bool Star::getDirect() const
{
    return direct_;
}

bool Star::canMove() const
{
    return true;
}

std::string Star::getType() const {
    return "star";
}

Vector2 Star::getVelocity() const {
    return velocity_;
}