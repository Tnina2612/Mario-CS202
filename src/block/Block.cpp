
#include "Block/Block.h"
#include "Block/BlockState.h"
#include "Block/QuestionBlock.h"
#include "Block/NormalBlock.h"
#include "Block/BreakBlock.h"
#include "Block/SolidBlock.h"
#include "Character.hpp"

Block::Block(Vector2 pos, int item_count, const std::string &type_item, const std::string &type_block)
    : sprite_(Item_Sprite::item_), pos_(pos), item_count_(item_count), type_item_(type_item)
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
    currentState_->Draw_();
}

void Block::update_()
{
    currentState_->Update_();
}

void Block::onHit(std::vector<Item *> &item,Character & character)
{
    currentState_->onHit(item, player, info);
}

void Block::setState(A_Block_State *new_state)
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
    return item_count_;
}

Rectangle Block::getSourceRec() const { return currentState_->getSourceRec(); }

Rectangle Block::getDrawRec() const { return currentState_->getDrawRec(); }

bool Block::getJiggle() const { return currentState_->getJiggle(); }

bool Block::getIsDelete() const { return currentState_->getIsDelete(); }

std::string Block::getTypeItem() const { return type_item_; }

void Block::decreaseItem()
{
    item_count_--;
}

const SpriteSheet &Block::getSprite()
{
    return sprite_;
}

BlockState *Block::getQuestionState() const
{
    return questionState_;
}

NormalBlock *Block::getNormalState() const
{
    return normalState_;
}

BlockState *Block::GetSolidState() const
{
    return solidState_;
}

BlockState *Block::GetBreakState() const
{
    return breakState_;
}