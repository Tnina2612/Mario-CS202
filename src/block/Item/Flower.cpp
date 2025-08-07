#include "../include/Block/Item/Flower.h"

Flower::Flower(Vector2 pos)
    : Item(pos), isAppear(0), beforePos(pos)
{
    rec_ = ItemSprite::FIREFLOWER1[0];
}

void Flower::update()
{
    appear();
}

// void Flower::activate(Character &character){
//     if (isDelete())
//         return;

//     if (character.getCharacterState() == CharacterState::Fire)
//     {
//         character.setState(new FireState(character));
//     }
//     else
//     {
//         character.setState(new SuperState(character));
//     }

//     appearAnimation = 0;
//     beforePos = pos_;
//     pos_.y -= tileSize;
// }
// {
//     Score_Manager &score_manager = Score_Manager::GetInstance();
//     score_manager.AddScore({character.getPosition().x + character.get_draw_rec().width, character.getPosition().y}, Score_Flower);
//     character.getFlower();
//     info.UpdateScore(ScoreFlower);
//     isDelete = 1;
// }

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
