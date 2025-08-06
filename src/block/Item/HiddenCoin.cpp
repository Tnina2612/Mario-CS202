#include "Item/HiddenCoin.h"

HiddenCoin::HiddenCoin(Vector2 pos)
    : Item(pos),
      m_rec(Item_Sprite::Coin::Hidden::hidden_),
      velocity_({0.0f, -Push_Height}),
      before_pos_(pos)
{
    rec_ = m_rec[0];

    const float gravity = Physics::gravity_;                       // 1000.0f
    const float total_air_time = 2 * Push_Height / gravity * 0.8f; // 1.0f

    sprite_interval_ = total_air_time / static_cast<float>(m_rec.size());
}

void HiddenCoin::update_()
{
    appear_();
}

void HiddenCoin::Appear_()
{
    const float gravity = Physics::gravity_;

    // Cập nhật animation theo thời gian
    frame_ += GetFrameTime();
    if (frame_ >= sprite_interval_)
    {
        frame_ = 0.0f;
        type_++;

        if (type_ < m_rec.size())
            rec_ = m_rec[type_];
        else
            is_delete = true;
    }

    // Physics
    velocity_.y += gravity * GetFrameTime();
    pos_.y += velocity_.y * GetFrameTime();

    if (pos_.y >= before_pos_.y)
    {
        pos_.y = before_pos_.y;
        is_delete = true;
    }
}

void HiddenCoin::Activate_(Player &player, PlayerInformation &info)
{
    player.collectCoin();
    info.UpdateCoins(1);
}

bool HiddenCoin::Can_Move() const
{
    return false;
}
