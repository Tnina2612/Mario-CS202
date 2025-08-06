#include "block/SolidBlock.h"

const scale_screen = 3.0f;

SolidBlock::SolidBlock(Block &m_block)
    : m_block(m_block)
{
    rec_ = Item_Sprite::Brown_Brick::type_1;
}

void SolidBlock::draw_()
{
    Rectangle dest_rec = {
        m_block.getPos().x,
        m_block.getPos().y,
        rec_.width * scale_screen,
        rec_.height * scale_screen};
    DrawTexturePro(
        m_block.getSprite().sprite,
        rec_,
        dest_rec,
        {dest_rec.width / 2.0f, dest_rec.height},
        0.0f,
        WHITE);
}

bool SolidBlock::getJiggle() { return false; }

Rectangle SolidBlock::getDrawRec() const { return {m_block.getPos().x - rec_.width * scale_screen / 2.0f, m_block.getPos().y - rec_.height * scale_screen, rec_.width * scale_screen, rec_.height * scale_screen}; }