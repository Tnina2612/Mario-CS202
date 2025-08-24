#include <Block/BreakBlock.h>
#include <core/SoundManager.hpp>

const float scale_screen = 3.0f;
BreakBlock::BreakBlock(Block &block/*, Animation* animation*/)
    : m_block(block), isDelete(false), rotation(0.0f), debris("debris")
{
    before_pos = {m_block.getPos().x, m_block.getPos().y - rec_.y};
    up_pos_left = down_pos_left = before_pos;

    up_velocity = {-move_, -breakHeight}; // bay lên
    down_velocity = {-move_, 0.0f};        // rơi xuống từ từ
    SoundManager::getInstance().playSound(SoundType::BREAKBLOCK);
}

void BreakBlock::draw_()
{
    Vector2 dest_up_left = {up_pos_left.x, up_pos_left.y};
    Vector2 dest_up_right = {before_pos.x + (before_pos.x - up_pos_left.x), up_pos_left.y};
    Vector2 dest_down_left = {down_pos_left.x, down_pos_left.y};
    Vector2 dest_down_right = {before_pos.x + (before_pos.x - down_pos_left.x), down_pos_left.y};
    debris.draw(dest_up_left.x, dest_up_left.y, 0.f);
    debris.draw(dest_up_right.x, dest_up_left.y, 90.f);
    debris.draw(dest_down_left.x, dest_up_left.y, 180.f);
    debris.draw(dest_down_right.x, dest_up_left.y, 270.f);
}

void BreakBlock::update_()
{
    fall();
    beDelete();
}

bool BreakBlock::getJiggle() { return true; }

bool BreakBlock::getIsDelete() const { return isDelete; }

void BreakBlock::fall()
{
    float dt = GetFrameTime();

    // Cập nhật vận tốc theo gia tốc trọng lực
    up_velocity.y += 1000.0f * dt;
    down_velocity.y += 1000.0f * dt;

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

void BreakBlock::beDelete()
{
    if (up_pos_left.y - rec_.y * scale_screen / 2.0f >= 240)
        isDelete = true;
}

Rectangle BreakBlock::getDrawRec() const
{
    return {
        m_block.getPos().x,
        m_block.getPos().y,
        rec_.x,
        rec_.y};
}

std::string BreakBlock::getStateName() const {
    return "Break";
}

shared_ptr<BlockState> BreakBlock::clone(Block& m_block) const {
    shared_ptr<BlockState> ret = make_shared<BreakBlock>(m_block);
    return ret;
}