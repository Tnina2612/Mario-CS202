#pragma once
#include "Block.h"
#include "BlockState.h"
#include "../entities/Character.hpp"
class BreakBlock : public BlockState
{
private:
    Texture2D blockTexture;
    Rectangle rec_;
    Block &m_block;
    bool isDelete;
    Vector2 up_pos_left, down_pos_left;
    Vector2 up_velocity, down_velocity;
    const float move_ = 120.0f;
    float rotation;
    const float rotationSpeed = 15.0f;
    const float breakHeight = 400.0f;
    Vector2 before_pos;
    void fall();
    void beDelete();
    Animation* animation_;

public:
    BreakBlock(Block &block/*, Animation* animation*/);
    void draw_() override;
    void update_() override;
    void onHit(std::vector<Item *> &item, Character & character) override {}
    bool getJiggle() override;
    bool getIsDelete() const override;
    Rectangle getDrawRec() const override;
};