#pragma once
#include "Block.h"
#include "BlockState.h"
#include "../entities/Character.hpp"
#include <entities/Animation.hpp>
class BreakBlock : public BlockState
{
private:
    AnimationVectorTexture debris;
    Block &m_block;
    bool isDelete;
    Vector2 up_pos_left, down_pos_left;
    Vector2 up_velocity, down_velocity;
    const float move_ = 80.0f;
    float rotation;
    const float rotationSpeed = 10.0f;
    const float breakHeight = 150.0f;
    Vector2 before_pos;
    void fall();
    void beDelete();

public:
    BreakBlock(Block &block);
    void draw_() override;
    void update_() override;
    void onHit(const std::vector<Item*> &item, Character & character) override {}
    bool getJiggle() override;
    bool getIsDelete() const override;
    Rectangle getDrawRec() const override;
    std::string getStateName() const override;
};