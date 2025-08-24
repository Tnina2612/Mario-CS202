#include "../include/Block/Item/Flower.h"

Flower::Flower(Vector2 pos)
    : Item(pos), isAppear(0), beforePos(pos), 
    m_rec(ItemSprite::FIREFLOWER1), frameTime(1.0f / 60.0f) 
{
}

void Flower::update()
{
    appear();
    frame_ += GetFrameTime();
    if (frame_ >= frameTime)
    {
        type_ = (type_ + 1) % m_rec.size();
        frame_ = 0.0f;
    }
    rec_ = m_rec[type_];
}

void Flower::activate(Character &character){
//     if (isDelete())
//         return;

    character.powerUp();
//     Score_Manager &score_manager = Score_Manager::GetInstance();
//     score_manager.AddScore({character.getPosition().x + character.get_draw_rec().width, character.getPosition().y}, Score_Flower);
//     character.getFlower();
//     info.UpdateScore(ScoreFlower);
    isDelete_ = 1;
}

void Flower::appear()
{
    if (isAppear)
        return;
    pos_.y -= appearAnimation;
    if (pos_.y <= beforePos.y - tileSize)
    {
        isAppear = 1;
        appearAnimation = 0;
        pos_.y = beforePos.y - tileSize;
    }
}

bool Flower::canMove() const { return false; }

std::string Flower::getType() const {
    return "flower";
}

Vector2 Flower::getVelocity() const {
    return {0.0f, 0.0f};
}

shared_ptr<Item> Flower::clone() const {
    shared_ptr<Item> ret = make_shared<Flower>(beforePos);
    return ret;
}