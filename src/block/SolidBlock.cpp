#include "block/SolidBlock.h"
#include "../assets/images/Coordinate.h"
const float scale_screen = 3.0f;

SolidBlock::SolidBlock(Block &m_block)
    : m_block(m_block)
{
    // rec_ =... 
}

void SolidBlock::draw_()
{
    
}

bool SolidBlock::getJiggle() { return false; }

Rectangle SolidBlock::getDrawRec() const { 
    return {
        m_block.getPos().x,
        m_block.getPos().y,
        rec_.x,
        rec_.y};
}

std::string SolidBlock::getStateName() const {
    return "Solid";
}

shared_ptr<BlockState> SolidBlock::clone(Block& m_block) const {
    shared_ptr<BlockState> ret = make_shared<SolidBlock>(m_block);
    return ret;
}