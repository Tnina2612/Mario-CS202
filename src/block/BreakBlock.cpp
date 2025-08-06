#include "Block/BreakBlock.h"
const float scale_screen = 3.0f;
BreakBLock::BreakBLock(Block &block)
    : m_block(block), isDelete(false), rotation(0.0f)
{
    rec_ = ItemSprite::Brown_Brick::break_;
    before_pos = {m_block.getPos().x, m_block.getPos().y - rec_.height};
    up_pos_left = down_pos_left = before_pos;

    up_velocity = {-move_, -breakHeight}; // bay lên
    down_velocity = {-move_, 0.0f};        // rơi xuống từ từ
}

void BreakBLock::draw_()
{
    Vector2 origin = {rec_.width * scale_screen / 2.0f, rec_.height * scale_screen / 2.0f};

    Rectangle dest_rec_up_left = {
        up_pos_left.x,
        up_pos_left.y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};

    Rectangle dest_rec_up_right = {
        before_pos.x + (before_pos.x - up_pos_left.x),
        up_pos_left.y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};

    Rectangle dest_rec_down_left = {
        down_pos_left.x,
        down_pos_left.y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};

    Rectangle dest_rec_down_right = {
        before_pos.x + (before_pos.x - down_pos_left.x),
        down_pos_left.y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};

    DrawTexturePro(m_block.Get_Sprite().sprite, rec_, dest_rec_up_left, origin, rotation, WHITE);
    DrawTexturePro(m_block.Get_Sprite().sprite, rec_, dest_rec_up_right, origin, rotation, WHITE);
    DrawTexturePro(m_block.Get_Sprite().sprite, rec_, dest_rec_down_left, origin, rotation, WHITE);
    DrawTexturePro(m_block.Get_Sprite().sprite, rec_, dest_rec_down_right, origin, rotation, WHITE);
}

void BreakBLock::update_()
{
    fall();
    beDelete();
}

bool BreakBLock::getJiggle() { return true; }

bool BreakBLock::getIsDelete() const { return isDelete; }

void BreakBLock::fall()
{
    float dt = GetFrameTime();

    // Cập nhật vận tốc theo gia tốc trọng lực
    up_velocity.y += Physics::gravity_ * dt;
    down_velocity.y += Physics::gravity_ * dt;

    // Cập nhật vị trí
    up_pos_left.x += up_velocity.x * dt;
    up_pos_left.y += up_velocity.y * dt;

    down_pos_left.x += down_velocity.x * dt;
    down_pos_left.y += down_velocity.y * dt;

    // Cố định block gốc để không vẽ nữa
    m_block.setPos({0, 0});

    // Xoay
    rotation += rotationSpeed;
    if (rotation >= 360.0f)
        rotation = 0.0f;
}

void BreakBLock::beDelete()
{
    if (up_pos_left.y - rec_.height * scale_screen / 2.0f >= Screen_h)
        isDelete = true;
}

Rectangle BreakBLock::getDrawRec() const
{
    return {
        m_block.getPos().x - Tile_Size / 2.0f,
        m_block.getPos().y - Tile_Size,
        Tile_Size,
        Tile_Size};
}
