#include<level/LevelPlayerAnimation.hpp>

PlayerDownPipeAnimation::PlayerDownPipeAnimation(Character* player) : 
    player(player), targetY(player->getPos().y + player->getRectangle().height) 
{
    // Constructor
}

bool PlayerDownPipeAnimation::isDone() {
    return player->getPos().y >= targetY;
}
void PlayerDownPipeAnimation::update() {
    player->intoPipeAnimation.goDownward();
}

PlayerIntoLeftPipeAnimation::PlayerIntoLeftPipeAnimation(Character* player) :
    player(player), targetX(player->getPos().x - player->getRectangle().width) 
{
    // Constructor
}

bool PlayerIntoLeftPipeAnimation::isDone() {
    return player->getPos().x <= targetX;
}

void PlayerIntoLeftPipeAnimation::update() {
    player->intoPipeAnimation.goLeftward();
}

PlayerIntoRightPipeAnimation::PlayerIntoRightPipeAnimation(Character* player) :
    player(player), targetX(player->getPos().x + player->getRectangle().width)
{
    // Constructor
}

bool PlayerIntoRightPipeAnimation::isDone() {
    return player->getPos().x >= targetX;
}
    
void PlayerIntoRightPipeAnimation::update() {
    player->intoPipeAnimation.goRightward();
}

PlayerUpPipeAnimation::PlayerUpPipeAnimation(Character* player) :
    player(player), targetY(player->getPos().y - player->getRectangle().height) 
{
    // Constructor
}

bool PlayerUpPipeAnimation::isDone() {
    return player->getPos().y <= targetY;
}

void PlayerUpPipeAnimation::update() {
    player->intoPipeAnimation.goUpward();
}