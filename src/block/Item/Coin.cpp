#include "../include/Block/Item/Coin.h"

Coin::Coin(Vector2 pos)
    : Item(pos), m_rec(ItemSprite::COINSPIN) {}

void Coin::update()
{
    appearAnimation = 0;
    frame_ += GetFrameTime();
    if (frame_ >= 1 / 6.0f)
    {
        type_ = (type_ + 1) % m_rec.size();
        frame_ = 0.0f;
    }
    rec_ = m_rec[type_];
}

void Coin::appear() {
    
}

void Coin::activate(Character &character)
{
//     character.UpdateCoins(1);
//     isDelete_ = 1;
}

bool Coin::canMove() const { return false; }