
#include "../include/Block/Block.h"
#include "../include/Block/BlockState.h"
#include "../include/Block/QuestionBlock.h"
#include "../include/Block/NormalBlock.h"
#include "../include/Block/BreakBlock.h"
#include "../include/Block/SolidBlock.h"
#include "../include/entities/Character.hpp"
#include "../assets/images/Coordinate.h"
#include <diy_functions/strsplit.h>

Block::Block(Vector2 pos, const std::string &blockData)
    : pos_(pos), animation(strsplit(blockData,':')[0]), nameBlock(blockData), 
    nextState_(nullptr),
    items(Item::stringToVectorItem(blockData, pos.x + 8, pos.y + 16))
{
    // Constructor
    currentState_ = (getBlockState(blockData));
}

Block::~Block()
{
    currentState_.reset();
}

void Block::draw_()
{
    currentState_->draw_();
    animation.draw(pos_.x, pos_.y);
}

void Block::update_()
{
    if(nextState_ != nullptr) {
        currentState_ = nextState_;
        nextState_.reset();
    }
    currentState_->update_();
    animation.update(); 
}

void Block::onHit(Character & character)
{
    currentState_->onHit(character);
}

void Block::setState(std::shared_ptr<BlockState> new_state)
{
    nextState_ = new_state;
}

std::string Block::getStateName() const {
    return currentState_->getStateName();
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
    return items.size();
}

Rectangle Block::getDrawRec() const { return currentState_->getDrawRec(); }

bool Block::getJiggle() const { return currentState_->getJiggle(); }

bool Block::getIsDelete() const { return currentState_->getIsDelete(); }

std::string Block::getBlockName() const { return nameBlock; }

void Block::appearItem(Character& player)
{
    appearingItem = items.back();
    if(appearingItem->getType() == "mushroom" + to_string(StateMushroom::super_) || appearingItem->getType() == "flower") {
        if(player.getCharacterState() == CharacterState::SMALL) {
            appearingItem = make_shared<Mushroom>(items.back()->getPos(), StateMushroom::super_);
        } else {
            appearingItem = make_shared<Flower>(items.back()->getPos());
        }
    }
    appearingItem->appear();
    items.pop_back();

    if(appearingItem->getType() == "coin") {
        // player.addCoin();
    }
}

std::shared_ptr<BlockState> Block::getBlockState(const std::string& blockData) {
    std::string name = strsplit(blockData, ':')[0];
    if(name.find("question") != std::string::npos) {
        return std::make_shared<QuestionBlock>(*this);
    } else if(name.find("brick") != std::string::npos) {
        return std::make_shared<NormalBlock>(*this);
    } 
    return std::make_shared<SolidBlock>(*this);
}

std::shared_ptr<Item> Block::popAppearingItem() {
    std::shared_ptr<Item> ret = move(appearingItem);
    return ret;
}