#include<block/InvisibleBlock.h>
#include<block/SolidBlock.h>

InvisibleBlock::InvisibleBlock(Block &m_block)
    : m_block(m_block), changeState_(false)
{
    // Constructor
}

void InvisibleBlock::draw_()
{
    // Do nothing, invisible block does not draw anything
}

void InvisibleBlock::update_()
{
    changeState();
}

void InvisibleBlock::onHit(Character &character)
{
    if(m_block.getItemCount() > 0) {
        m_block.appearItem(character);
    }
    changeState_ = true;
}

bool InvisibleBlock::getJiggle()
{
    return false; // Invisible block does not jiggle
}

void InvisibleBlock::changeState()
{
    if(changeState_) {
        m_block.setState(make_shared<SolidBlock>(m_block));
        m_block.animation = AnimationVectorTexture("G4");
        changeState_ = false; 
    }
}

Rectangle InvisibleBlock::getDrawRec() const
{
    return Rectangle{m_block.getPos().x, m_block.getPos().y, rec_.x, rec_.y};
}

std::string InvisibleBlock::getStateName() const
{
    return "Invisible";
}