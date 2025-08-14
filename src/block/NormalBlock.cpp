#include "Block/NormalBlock.h"
#include<block/BreakBlock.h>
#include<block/SolidBlock.h> 
const float scale_screen= 3.0f;

NormalBlock::NormalBlock(Block &block)
    : m_block(block), jiggle_(false), changeState_(false), velocity_y(0.0f), isBreak(m_block.items.empty())
{
    before_pos = m_block.getPos();
    // rec_ = ItemSprite::;

    // isBreak = (m_block.getTypeItem() == "");
}

void NormalBlock::draw_()
{
}

void NormalBlock::update_()
{
    jiggle();
    changeState();
}

void NormalBlock::onHit(Character& character)
{
    if (m_block.getItemCount() > 0)
    {
        m_block.appearItem(character);
        jiggle_ = true;
        velocity_y = -pushHeight; // đẩy lên
        if (m_block.getItemCount() == 0)
        {
            changeState_ = true;
            return;
        }
    }
    else if (m_block.getItemCount() == 0 &&
             (character.getCharacterState() == CharacterState::SMALL/* || character.getCharacterState() == CharacterState::INVINCIBLE*/))
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
    float dt = GetFrameTime();
    velocity_y += 1000.0f * dt;

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
    if (changeState_ && isBreak)
    {
        m_block.setState(make_shared<BreakBlock>(m_block));
    }
    else if (changeState_ && !isBreak && !jiggle_)
    {
        m_block.setState(make_shared<SolidBlock>(m_block));
        m_block.animation = AnimationVectorTexture("G4");
    }
}

Rectangle NormalBlock::getDrawRec() const
{
    return {
        m_block.getPos().x,
        m_block.getPos().y,
        rec_.x,
        rec_.y};
}

bool NormalBlock::getJiggle()
{
    return jiggle_ || changeState_;
}

std::string NormalBlock::getStateName() const {
    return "Normal";
}