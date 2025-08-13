#pragma once
#include <raylib.h>
#include <memory>
#include "BlockState.h"
#include "Item/ItemFactory.h"
#include "../include/entities/Character.hpp"
#include "../assets/images/Coordinate.h"

class Block
{
    friend class BlockState;
    friend class NormalBlock;
    friend class QuestionBlock;
private:
    std::shared_ptr<BlockState> currentState_;
    std::shared_ptr<BlockState> nextState_;

    Vector2 pos_;
    int itemCount;
    std::string typeItem;
    std::string name_block;
    AnimationVectorTexture animation;
public:
    Block(Vector2 pos, int itemCount, const std::string &typeItem, const std::string &typeBlock, const std::string &name_block);
    ~Block();
    std::vector<bool> surroundedBlock{0, 0, 0, 0}; 
    void update_();
    void draw_();
    void onHit(const std::vector<Item*> &item, Character & character);

    void setState(std::shared_ptr<BlockState> new_state);
    std::string getStateName(void) const;

    Vector2 getPos() const;
    void setPos(Vector2 pos);
    int getItemCount() const;
    Rectangle getDrawRec() const;
    bool getJiggle() const;
    bool getIsDelete() const;
    std::string getTypeItem() const;
    std::string getBlockName() const;
    void decreaseItem();
};