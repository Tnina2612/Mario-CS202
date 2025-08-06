#include "Item/MushRoom.h"
#include <iostream>

Mush_Room::Mush_Room(Vector2 pos, State_MushRoom state)
    : Item(pos), state_(state), direct_(1), fall_(false), is_appear(false), jump_(true), before_pos_({pos.x, pos.y - Tile_Size})
{
    velocity_ = {0.0f, 0.0f};
    previous_frame_pos = pos_;

    switch (state_)
    {
    case State_MushRoom::super_:
        rec_ = Item_Sprite::Mushroom::super_mushroom;
        break;
    case State_MushRoom::one_up:
        rec_ = Item_Sprite::Mushroom::one_up_mushroom;
        break;
    case State_MushRoom::posion_:
        rec_ = Item_Sprite::Mushroom::posion_mushroom;
        break;
    default:
        break;
    }
}

void Mush_Room::Notify_Fall()
{
    if (!jump_ && !fall_)
    {
        fall_ = true;
        velocity_.y = 0.0f; // bắt đầu rơi từ vận tốc đứng yên
    }
}

void Mush_Room::Notify_On_Ground()
{
    fall_ = false;
    jump_ = false;
    velocity_.y = 0.0f;
}

void Mush_Room::Notify_Change_Direct() { direct_ = !direct_; }

void Mush_Room::Notify_Jump()
{
    jump_ = true;
    fall_ = false;
    velocity_.y = -Mushroom_Ini_Velo;
}

void Mush_Room::Jump_()
{
    if (!is_appear || !jump_)
        return;

    float dt = GetFrameTime();
    velocity_.y += Physics::gravity_ * dt;
    pos_.y += velocity_.y * dt;

    float move = Mush_Room_And_Star_Speed * dt;
    pos_.x += direct_ ? move : -move;
}

void Mush_Room::Fall_()
{
    if (!is_appear || !fall_)
        return;

    float dt = GetFrameTime();
    velocity_.y += Physics::gravity_ * dt;
    pos_.y += velocity_.y * dt;
}

void Mush_Room::Move_()
{
    if (!is_appear || fall_ || jump_)
        return;

    // Thiết lập tốc độ ngang, không ảnh hưởng dọc
    velocity_.x = (direct_ ? 1 : -1) * Mush_Room_And_Star_Speed;
    velocity_.y = 0.0f;

    pos_.x += velocity_.x * GetFrameTime();

    // Chặn biên màn hình
    if (pos_.x >= 214 * 48.0f - rec_.width * scale_screen / 2.0f)
    {
        pos_.x = 214 * 48.0f - rec_.width * scale_screen / 2.0f;
        direct_ = !direct_;
    }
    else if (pos_.x <= rec_.width * scale_screen / 2.0f)
    {
        pos_.x = rec_.width * scale_screen / 2.0f;
        direct_ = !direct_;
    }
}

void Mush_Room::Appear_()
{
    if (is_appear)
        return;

    pos_.y -= Appear_Animation;
    if (pos_.y <= before_pos_.y)
    {
        appear_animation = 0;
        is_appear = true;
        pos_.y = before_pos_.y;
        previous_frame_pos = pos_;
    }
}

void Mush_Room::Be_Delete()
{
    if (pos_.y - rec_.height * scale_screen >= Screen_h)
        is_delete = true;
}

void Mush_Room::Update_()
{
    previous_frame_pos = pos_;
    Appear_();
    Move_();
    Fall_();
    Jump_();
    Be_Delete();
}

void Mush_Room::Activate_(Player &player, PlayerInformation &info)
{
    if (state_ == State_MushRoom::super_)
    {
        Score_Manager &score_manager = Score_Manager::GetInstance();
        score_manager.AddScore(player.getPosition(), Score_One_Up_Super);
        player.getMushroom();
    }
    info.UpdateScore(Score_One_Up_Super);

    is_delete = true;
}

Vector2 Mush_Room::Get_Previous_Frame_Pos() { return previous_frame_pos; }

bool Mush_Room::Get_Direct() const { return direct_; }

bool Mush_Room::Can_Move() const { return true; }
