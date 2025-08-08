
#include "../include/Block/Block.h"
#include "../include/Block/BlockState.h"
#include "../include/Block/QuestionBlock.h"
#include "../include/Block/NormalBlock.h"
#include "../include/Block/BreakBlock.h"
#include "../include/Block/SolidBlock.h"
#include "../include/entities/Character.hpp"
#include "../assets/images/Coordinate.h"
Block::Block(Vector2 pos, int item_count, const std::string &type_item, const std::string &type_block, const std::string &name_block)
    : pos_(pos), itemCount(item_count), typeItem(type_item), 
    animation(name_block), name_block(name_block), nextState_(nullptr)
{
    if (type_block == "question")
        currentState_ = make_shared<QuestionBlock>(*this);
    else if (type_block == "normal")
        currentState_ = make_shared<NormalBlock>(*this);
}

Block::~Block()
{
    currentState_.reset();
}

void Block::draw_()
{
    currentState_->draw_();
}

void Block::update_()
{
    if(nextState_ != nullptr) {
        currentState_ = nextState_;
        nextState_.reset();
    }
    currentState_->update_();
}

void Block::onHit(std::vector<Item *> &item,Character & character)
{
    currentState_->onHit(item, character);
}

void Block::setState(std::shared_ptr<BlockState> new_state)
{
    nextState_ = new_state;
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

Rectangle Block::getDrawRec() const { return currentState_->getDrawRec(); }

bool Block::getJiggle() const { return currentState_->getJiggle(); }

bool Block::getIsDelete() const { return currentState_->getIsDelete(); }

std::string Block::getTypeItem() const { return typeItem; }

std::string Block::getBlockName() const { return name_block; }

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