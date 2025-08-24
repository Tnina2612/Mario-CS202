#include "block/QuestionBlock.h"
#include<block/SolidBlock.h>
#include<core/SoundManager.hpp>

const float scale_screen = 3.0f; 

QuestionBlock::QuestionBlock(Block &block)
    : m_block(block), m_rec(), frame_(0.0f), type_(0), velocity_y(0.0f), jiggle_(false)
{
    before_pos = m_block.getPos();
    // rec_ = m_rec[type_];
}

void QuestionBlock::draw_()
{
//     Rectangle dest_rec = {
//         m_block.getPos().x,
//         m_block.getPos().y,
//         rec_.width * scale_screen,
//         rec_.height * scale_screen};
//     DrawTexturePro(
//         m_block.Get_Sprite().sprite,
//         rec_,
//         dest_rec,
//         {dest_rec.width / 2.0f, dest_rec.height},
//         0.0f,
//         WHITE);
}

void QuestionBlock::animation_()
{
    // frame_ += GetFrameTime();
    // if (frame_ >= 1 / 8.0f)
    // {
    //     type_ = (type_ + 1) % m_rec.size();
    //     frame_ = 0.0f;
    // }
    // rec_ = m_rec[type_];
}

void QuestionBlock::update_()
{
    animation_();
    jiggle();
    changeState();
}

void QuestionBlock::onHit(Character &character)
{
    if (m_block.getItemCount() > 0)
    {
        m_block.appearItem(character);
        jiggle_ = true;
        velocity_y = -pushHeight; // Đẩy lên
    } 
    if(m_block.getItemCount() == 0) {
        changeState_ = true;
    }
}

void QuestionBlock::jiggle()
{
    if (!jiggle_)
        return;

    SoundManager::getInstance().playSound(SoundType::BUMP);

    float dt = GetFrameTime();
    velocity_y += 1000.0f * dt;

    Vector2 tmp = m_block.getPos();
    tmp.y += velocity_y * dt;

    if (tmp.y >= before_pos.y)
    {
        tmp.y = before_pos.y;
        velocity_y = 0.0f;
        jiggle_ = false;
    }

    m_block.setPos(tmp);
}

void QuestionBlock::changeState()
{
    if (m_block.getItemCount() == 0 && !jiggle_ && changeState_)
    {
        m_block.setState(make_shared<SolidBlock>(m_block));
        m_block.animation = AnimationVectorTexture("G4");
    }
}

bool QuestionBlock::getJiggle() 
{
    return jiggle_;
}

Rectangle QuestionBlock::getDrawRec() const
{
    return {
        m_block.getPos().x,
        m_block.getPos().y,
        rec_.x,
        rec_.y};
}

std::string QuestionBlock::getStateName() const {
    return "Question";
}

shared_ptr<BlockState> QuestionBlock::clone(Block& m_block) const {
    shared_ptr<BlockState> ret = make_shared<QuestionBlock>(m_block);
    return ret;
}