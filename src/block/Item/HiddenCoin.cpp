#include "Item/HiddenCoin.h"

HiddenCoin::HiddenCoin(Vector2 pos)
    : Item(pos),
      m_rec(ItemSprite::COINSPIN),
      velocity_({0.0f, -pushHeight}),
      before_pos_(pos)
{
    rec_ = m_rec[0];

    const float gravity = 1000.0f;                       
    const float totalAirTime = 2 * pushHeight / gravity * 0.8f; 

    spriteInterval = totalAirTime / static_cast<float>(m_rec.size());
}

void HiddenCoin::update()
{
    appear();
}

void HiddenCoin::appear()
{
    const float gravity = 1000.0f;

    frame_ += GetFrameTime();
    if (frame_ >= spriteInterval)
    {
        frame_ = 0.0f;
        type_++;

        if (type_ < m_rec.size())
            rec_ = m_rec[type_];
        else
            isDelete_ = true;
    }

    // Physics
    velocity_.y += gravity * GetFrameTime();
    pos_.y += velocity_.y * GetFrameTime();

    if (pos_.y >= before_pos_.y)
    {
        pos_.y = before_pos_.y;
        isDelete_ = true;
    }
}

// void HiddenCoin::activate(Character &character)
// {
//     character.collectCoin();
//     character.getInfo().UpdateCoins(1);
// }

bool HiddenCoin::canMove() const
{
    return false;
}
