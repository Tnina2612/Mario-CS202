#include<level/LevelPlayerAnimation.hpp>

LevelPlayerAnimationManager::LevelPlayerAnimationManager(Character* character) : character(character) {}

void LevelPlayerAnimationManager::goDownward() {
    float x = character->getPos().x;
    float y = character->getPos().y + GetFrameTime() * LevelVar::animationSpeed;
    character->setPosition(x, y);
}

void LevelPlayerAnimationManager::goLeftward() {
    character->Animation::update(GetFrameTime(), 3, 3);
    float x = character->getPos().x - GetFrameTime() * LevelVar::animationSpeed;
    float y = character->getPos().y;
    character->setPosition(x, y);
}

void LevelPlayerAnimationManager::goRightward() {
    character->Animation::update(GetFrameTime(), 10, 3);
    float x = character->getPos().x + GetFrameTime() * LevelVar::animationSpeed;
    float y = character->getPos().y;
    character->setPosition(x, y);
}

void LevelPlayerAnimationManager::goUpward() {
    float x = character->getPos().x;
    float y = character->getPos().y - GetFrameTime() * LevelVar::animationSpeed;
    character->setPosition(x, y);
}

void LevelPlayerAnimationManager::climbDown(float pivotX) {
    // Set frame
    float x = pivotX;
    float y = character->getPos().y + GetFrameTime() * LevelVar::animationSpeed;
    character->setPosition(x, y);
}

void LevelPlayerAnimationManager::disappear() {
    character->Animation::setScale(0.0f);
}

void LevelPlayerAnimationManager::appear() {
    character->Animation::setScale(1.0f);
}

void PlayerDownPipeAnimation::initialize(Character* player) {
    this->player = player;
    targetY = player->getPos().y + player->getRectangle().height;
}

bool PlayerDownPipeAnimation::isDone() {
    return player->getPos().y >= targetY;
}
void PlayerDownPipeAnimation::update() {
    player->levelPlayerAnimationManager.goDownward();
}

string PlayerDownPipeAnimation::getType() const {
    return "Down";
}

void PlayerIntoLeftPipeAnimation::initialize(Character* player) {
    this->player = player;
    targetX = player->getPos().x - player->getRectangle().width;
}

bool PlayerIntoLeftPipeAnimation::isDone() {
    return player->getPos().x <= targetX;
}

void PlayerIntoLeftPipeAnimation::update() {
    player->levelPlayerAnimationManager.goLeftward();
}

string PlayerIntoLeftPipeAnimation::getType() const {
    return "Left";
}

void PlayerIntoRightPipeAnimation::initialize(Character* player) {
    this->player = player;
    targetX = player->getPos().x + player->getRectangle().width;
}

bool PlayerIntoRightPipeAnimation::isDone() {
    return player->getPos().x >= targetX;
}
    
void PlayerIntoRightPipeAnimation::update() {
    player->levelPlayerAnimationManager.goRightward();
}

string PlayerIntoRightPipeAnimation::getType() const {
    return "Right";
}

PlayerUpPipeAnimation::PlayerUpPipeAnimation(float targetY) : targetY(targetY) {}

void PlayerUpPipeAnimation::initialize(Character* player) {
    this->player = player;
}

bool PlayerUpPipeAnimation::isDone() {
    return player->getPos().y + player->getRectangle().height <= targetY;
}

void PlayerUpPipeAnimation::update() {
    player->levelPlayerAnimationManager.goUpward();
}

string PlayerUpPipeAnimation::getType() const {
    return "Up";
}

PlayerClimbDownAnimation::PlayerClimbDownAnimation(float pivotX, float targetY) : pivotX(pivotX), targetY(targetY) {}

void PlayerClimbDownAnimation::initialize(Character* player) {
    this->player = player;
}

bool PlayerClimbDownAnimation::isDone() {
    return player->getPos().y + player->getRectangle().width >= targetY;
}

void PlayerClimbDownAnimation::update() {
    player->levelPlayerAnimationManager.climbDown(pivotX);
}

string PlayerClimbDownAnimation::getType() const {
    return "ClimbDown";
}

PlayerWalkToXAnimation::PlayerWalkToXAnimation(float targetX, TileMap* blocks) : targetX(targetX), blocks(blocks) {}

void PlayerWalkToXAnimation::initialize(Character* player) {
    this->player = player;
}

bool PlayerWalkToXAnimation::isDone() {
    return player->getPos().x >= targetX;
}

void PlayerWalkToXAnimation::update() {
    player->setVelocityX(0.f);
    if(player->getPos().x < targetX) {
        blocks->update(player);
        player->levelPlayerAnimationManager.goRightward();
    } else if(player->getPos().x > targetX) {
        blocks->update(player);
        player->levelPlayerAnimationManager.goLeftward();
    }
}

string PlayerWalkToXAnimation::getType() const {
    return "WalkToX";
}

void PlayerEnterDoorAnimation::initialize(Character* player) {
    this->player = player;
    targetTime = 0.5f;
    elapsedTime = 0.0f;
}

bool PlayerEnterDoorAnimation::isDone() {
    return elapsedTime >= targetTime;
}

void PlayerEnterDoorAnimation::update() {
    elapsedTime += GetFrameTime();
    player->levelPlayerAnimationManager.disappear();
}

string PlayerEnterDoorAnimation::getType() const {
    return "EnterDoor";
}

void PlayerExitDoorAnimation::initialize(Character* player) {
    this->player = player;
    targetTime = 0.5f;
    elapsedTime = 0.0f;
}

bool PlayerExitDoorAnimation::isDone() {
    return elapsedTime >= targetTime;
}

void PlayerExitDoorAnimation::update() {
    elapsedTime += GetFrameTime();
    player->Animation::update(GetFrameTime(), 6, 1);
    player->levelPlayerAnimationManager.appear();
}

string PlayerExitDoorAnimation::getType() const {
    return "ExitDoor";
}