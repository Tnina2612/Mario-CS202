#include "Block/NormalBlock.h"
const float scale_screen= 3.0f;

NormalBlock::NormalBlock(Block &block)
    : m_block(block), jiggle_(false), changeState_(false), velocity_y(0.0f)
{
    before_pos = m_block.getPos();
    rec_ = Item_Sprite::Brown_Brick::type_2;

    isBreak = (m_block.getTypeItem() == "");
}

void NormalBlock::draw_()
{
    Rectangle dest_rec = {
        m_block.getPos().x,
        m_block.getPos().y,
        rec_.width * 3.0f,
        rec_.height * 3.0f};

    DrawTexturePro(
        m_block.getSprite().sprite,
        rec_,
        dest_rec,
        {dest_rec.width / 2.0f, dest_rec.height},
        0.0f,
        WHITE);
}

void NormalBlock::update_()
{
    jiggle();
    changeState();
}

void NormalBlock::onHit(std::vector<Item *> &item, Character& character)
{
    if (m_block.getItemCount() > 0)
    {
        SpawnItem::Item_Spawn(m_block.getTypeItem(), item, m_block.getPos(), character);
        m_block.decreaseItem();
        jiggle_ = true;
        velocity_y = -pushHeight; // đẩy lên
        if (m_block.getItemCount() == 0)
        {
            changeState_ = true;
            return;
        }
    }
    else if (m_block.getItemCount() == 0 &&
             (character.getForm() == PlayerForm::Small || character.getForm() == PlayerForm::Invincible))
    {
        jiggle_ = true;
        velocity_y = -pushHeight; // đẩy lên
    }
    else
    {
        changeState_ = true;
    }
}

void NormalBlock::jiggle()
{
    if (!jiggle_)
        return;

    float dt = GetFrameTime();
    velocity_y += Physics::gravity_ * dt;

    Vector2 tmp = m_block.getPos();
    tmp.y += velocity_y * dt;

    // Nếu đã về lại vị trí cũ (hoặc vượt quá)
    if (tmp.y >= before_pos.y)
    {
        tmp.y = before_pos.y;
        velocity_y = 0.0f;
        jiggle_ = false;
    }

    m_block.setPos(tmp);
}

void NormalBlock::changeState()
{
    if (changeState && isBreak)
    {
        m_block.setState(m_block.getBreakState());
    }
    else if (changeState && !isBreak && !jiggle_)
    {
        m_block.setState(m_block.getSolidState());
    }
}

Rectangle NormalBlock::getDrawRec() const
{
    return {
        m_block.getPos().x - rec_.width * scale_screen / 2.0f,
        m_block.getPos().y - rec_.height * scale_screen,
        rec_.width * scale_screen,
        rec_.height * scale_screen};
}

bool NormalBlock::getJiggle()
{
    return jiggle_ || changeState;
}
