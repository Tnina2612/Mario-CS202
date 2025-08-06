#include "Item/Star.h"
#include <iostream>

Star::Star(Vector2 pos)
    : Item(pos),
      direct_(true),
      is_appear(false),
      before_pos(pos),
      velocity_({0.0f, -Star_Ini_Velo}),
      previous_frame_pos(pos)
{
    rec_ = Item_Sprite::Star::invincible_star;
}

void Star::Notify_On_Ground()
{
    if (velocity_.y != -Star_Ini_Velo)
    {
        velocity_.y = -Star_Ini_Velo;
        before_pos = pos_;
    }
}

void Star::Notify_Change_Direct()
{
    direct_ = !direct_;
}

void Star::Fall_(float dt)
{
    if (!is_appear)
        return;

    velocity_.y += Physics::gravity_ * dt;
    pos_.y += velocity_.y * dt;
}

void Star::Move_(float dt)
{
    if (!is_appear)
        return;

    float speed = Mush_Room_And_Star_Speed * dt;
    if (direct_)
        pos_.x += speed;
    else
        pos_.x -= speed;

    // Va chạm biên
    float left_bound = rec_.width * scale_screen / 2.0f;
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

void Star::Appear_()
{
    if (is_appear)
        return;

    pos_.y -= Appear_Animation;

    if (pos_.y <= before_pos.y - Tile_Size)
    {
        appear_animation = false;
        is_appear = true;
        pos_.y = before_pos.y - Tile_Size;
        before_pos = pos_;
        previous_frame_pos = pos_;

        // Bắt đầu nhảy lên
        velocity_.y = -Star_Ini_Velo;
    }
}

void Star::Be_Delete()
{
    if (pos_.y - rec_.height * scale_screen >= Screen_h)
        is_delete = true;
}

void Star::Update_()
{
    float dt = GetFrameTime();
    previous_frame_pos = pos_;

    Appear_();
    Move_(dt);
    Fall_(dt);
    Be_Delete();
}

void Star::Activate_(Player &player, PlayerInformation &info)
{
    player.getStar();
    info.UpdateScore(Score_Star);
    is_delete = true;
}

Vector2 Star::Get_Previous_Frame_Pos()
{
    return previous_frame_pos;
}

bool Star::Get_Direct() const
{
    return direct_;
}

bool Star::Can_Move() const
{
    return true;
}
