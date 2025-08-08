
#include "../include/Block/Block.h"
#include "../include/Block/BlockState.h"
#include "../include/Block/QuestionBlock.h"
#include "../include/Block/NormalBlock.h"
#include "../include/Block/BreakBlock.h"
#include "../include/Block/SolidBlock.h"
#include "../include/entities/Character.hpp"
#include "../assets/images/Coordinate.h"
Block::Block(Vector2 pos, int item_count, const std::string &type_item, const std::string &type_block)
    : sprite_(LoadTexture("item.png")), pos_(pos), itemCount(item_count), typeItem(type_item)
{
    questionState_ = new QuestionBlock(*this);
    normalState_ = new NormalBlock(*this);
    solidState_ = new SolidBlock(*this);
    breakState_ = new BreakBlock(*this);
    if (type_block == "question")
        currentState_ = questionState_;
    else if (type_block == "normal")
        currentState_ = normalState_;
}

Block::~Block()
{
    delete questionState_;
    delete normalState_;
    delete breakState_;
    delete solidState_;
    currentState_ = nullptr;
}

void Block::draw_()
{
    currentState_->draw_();
}

void Block::update_()
{
    currentState_->update_();
}

void Block::onHit(std::vector<Item *> &item,Character & character)
{
    currentState_->onHit(item, character);
}

void Block::setState(BlockState *new_state)
{
    currentState_ = new_state;
}

Vector2 Block::getPos() const
{
    return pos_;
}

void Block::setPos(Vector2 pos)
{
    pos_ = pos;
}

int Block::getItemCount() const
{
    return itemCount;
}

Rectangle Block::getSourceRec() const { return currentState_->getSourceRec(); }

Rectangle Block::getDrawRec() const { return currentState_->getDrawRec(); }

bool Block::getJiggle() const { return currentState_->getJiggle(); }

bool Block::getIsDelete() const { return currentState_->getIsDelete(); }

std::string Block::getTypeItem() const { return typeItem; }

void Block::decreaseItem()
{
    itemCount--;
}

// const SpriteSheet &Block::getSprite()
// {
//     return sprite_;
// }

// BlockState *Block::getQuestionState() const
// {
//     return questionState_;
// }

// NormalBlock *Block::getNormalState() const
// {
//     return normalState_;
// }

// BlockState *Block::GetSolidState() const
// {
//     return solidState_;
// }

// BlockState *Block::GetBreakState() const
// {
//     return breakState_;
// }