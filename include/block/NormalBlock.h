#pragma once
#include "../include/block/Block.h"
#include "BlockState.h"

class NormalBlock : public BlockState
{
private:
    Block &m_block;
    bool jiggle_;
    bool changeState_;
    bool isBreak;
    Vector2 before_pos;
    float velocity_y;
    const float pushHeight = 100.0f;
    void jiggle();
    void changeState();

public:
    NormalBlock(Block &m_block);
    void draw_() override;
    void update_() override;
    void onHit(const std::vector<Item*> &item, Character & character) override;
    bool getJiggle() override;
    Rectangle getDrawRec() const override;
    std::string getStateName() const override;
};