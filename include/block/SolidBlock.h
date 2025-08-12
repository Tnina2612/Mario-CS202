#pragma once
#include "Block.h"
#include "BlockState.h"

class SolidBlock : public BlockState
{
private:
    Block &m_block;

public:
    SolidBlock(Block &block);
    void draw_() override;
    void update_() override {}
    void onHit(const std::vector<Item*> &item, Character &character) override {}
    bool getJiggle() override;
    Rectangle getDrawRec() const override;
    std::string getStateName() const override;
};