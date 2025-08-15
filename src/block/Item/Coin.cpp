#include "../include/Block/Item/Coin.h"

Coin::Coin(Vector2 pos)
    : Item(pos), m_rec(ItemSprite::COINSPIN), initY(pos.y),
    targetY(48.f), velocityY(-192), frameTime(1.f/60.f) {
}

void Coin::update()
{
    if(appearAnimation == false) return;
    frame_ += GetFrameTime();
    if (frame_ >= frameTime)
    {
        type_ = (type_ + 1) % m_rec.size();
        frame_ = 0.0f;
    }
    rec_ = m_rec[type_];
    pos_.y += GetFrameTime() * velocityY;
    if(pos_.y <= initY - targetY) {
        isDelete_ = true;
    }
}

void Coin::appear() {
    appearAnimation = true;
}

bool Coin::canMove() const { return false; }

std::string Coin::getType() const {
    return "coin";
}

Vector2 Coin::getVelocity() const {
    return {0.0f, velocityY};
}