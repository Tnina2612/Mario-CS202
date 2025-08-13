#include "block/Item/Star.h"
#include <iostream>
const float scale_screen = 3.0f;
Star::Star(Vector2 pos)
    : Item(pos),
      direct_(true),
      isAppear(false),
      beforePos(pos),
      velocity_({0.0f, -starIniVelo}),
      previousFramePos(pos)
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

    // Va chạm biên
    float left_bound = rec_.width * 3.0f / 2.0f;
    float right_bound = 214 * 48.0f - left_bound;

    if (pos_.x >= right_bound)
    {
        pos_.x = right_bound;
        direct_ = !direct_;
    }
    else if (pos_.x <= left_bound)
    {
        pos_.x = left_bound;
        direct_ = !direct_;
    }
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

        // Bắt đầu nhảy lên
        velocity_.y = -starIniVelo;
    }
}

void Star::beDelete()
{
    if (pos_.y - rec_.height * scale_screen >= 240)
        isDelete_ = true;
}

void Star::update()
{
    float dt = GetFrameTime();
    previousFramePos = pos_;

    appear();
    move(dt);
    fall(dt);
    beDelete();
}

void Star::activate(Character &character)
{
//     character.getStar();
//     character.updateScore(Score_Star);
//     isDelete_ = true;
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