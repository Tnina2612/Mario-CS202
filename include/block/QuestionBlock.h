#pragma once
#include "Block.h"
#include "BlockState.h"

class QuestionBlock : public BlockState
{
private:
    Block &m_block;
    std::vector<Rectangle> m_rec;
    float frame_;
    int type_;
    Vector2 before_pos;
    float velocity_y;
    const float pushHeight = 100.0f;
    bool jiggle_;
    bool changeState_ = false;
    void animation_();
    void jiggle();
    void changeState();

public:
    QuestionBlock(Block &m_block);
    void draw_() override;
    void update_() override;
    void onHit(Character &character) override;
    bool getJiggle() override;
    Rectangle getDrawRec() const override;
    std::string getStateName() const override;
};