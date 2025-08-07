#pragma once
#include <raylib.h>
#include <memory>
#include "BlockState.h"
#include "Item/ItemFactory.h"
#include "../include/entities/Character.hpp"
#include "../assets/images/Coordinate.h"

class Block
{
private:
    Texture2D sprite_;

    BlockState *questionState_;
    BlockState *normalState_;
    BlockState *solidState_;
    BlockState *breakState_;
    BlockState *currentState_;

    Vector2 pos_;
    int itemCount;
    std::string typeItem;

public:
    Block(Vector2 pos, int itemCount, const std::string &typeItem, const std::string &typeBlock);
    ~Block();
    std::vector<bool> surroundedBlock{0, 0, 0, 0}; 
    void update_();
    void draw_();
    void onHit(std::vector<Item *> &item, Character & character);

    void setState(BlockState *new_state);

    Vector2 getPos() const;
    void setPos(Vector2 pos);
    int getItemCount() const;
    Rectangle getSourceRec() const;
    Rectangle getDrawRec() const;
    bool getJiggle() const;
    bool getIsDelete() const;
    std::string getTypeItem() const;
    void decreaseItem();

    BlockState *getQuestionState() const;
    BlockState *getNormalState() const;
    BlockState *getSolidState() const;
    BlockState *getBreakState() const;
};