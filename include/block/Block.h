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
    std::string nameBlock;
    AnimationVectorTexture animation;
    std::vector<shared_ptr<Item>> items;
    shared_ptr<Item> appearingItem;
public:
    Block(Vector2 pos, const std::string &blockData);
    ~Block();
    std::vector<bool> surroundedBlock{0, 0, 0, 0}; 
    void update_();
    void draw_();
    void onHit(Character & character);
    void setState(std::shared_ptr<BlockState> new_state);
    std::string getStateName(void) const;
    Vector2 getPos() const;
    void setPos(Vector2 pos);
    int getItemCount() const;
    Rectangle getDrawRec() const;
    bool getJiggle() const;
    bool getIsDelete() const;
    std::string getBlockName() const;
    void appearItem(Character& player);
    std::shared_ptr<BlockState> getBlockState(const std::string& blockData);
    std::shared_ptr<Item> popAppearingItem();
    // std::vector<Item> to_items(const std::string& blockData);
};