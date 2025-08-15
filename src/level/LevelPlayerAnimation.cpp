#include<level/LevelPlayerAnimation.hpp>

PlayerLevelAnimationManager::PlayerLevelAnimationManager(Character* character) : character(character) {}

void PlayerLevelAnimationManager::goDownward() {
    float x = character->getPos().x;
    float y = character->getPos().y + GetFrameTime() * LevelVar::animationSpeed;
    character->setPosition(x, y);
}

void PlayerLevelAnimationManager::goLeftward() {
    character->getAnimation().update(GetFrameTime(), 3, 3);
    float x = character->getPos().x - GetFrameTime() * LevelVar::animationSpeed;
    float y = character->getPos().y;
    character->setPosition(x, y);
}

void PlayerLevelAnimationManager::goRightward() {
    character->getAnimation().update(GetFrameTime(), 10, 3);
    float x = character->getPos().x + GetFrameTime() * LevelVar::animationSpeed;
    float y = character->getPos().y;
    character->setPosition(x, y);
}

void PlayerLevelAnimationManager::goUpward() {
    float x = character->getPos().x;
    float y = character->getPos().y - GetFrameTime() * LevelVar::animationSpeed;
    character->setPosition(x, y);
}

void PlayerLevelAnimationManager::climbDown(float pivotX) {
    // Set frame
    float x = pivotX;
    float y = character->getPos().y + GetFrameTime() * LevelVar::animationSpeed;
    character->setPosition(x, y);
}

void PlayerLevelAnimationManager::disappear() {
    character->getAnimation().setScale(0.0f);
}

void PlayerLevelAnimationManager::appear() {
    character->getAnimation().setScale(1.0f);
}

void PlayerLevelAnimationManager::grow() {
    bool doneAnimation;
    if(character->getOrientation() == LEFT) doneAnimation = character->getAnimation().update({0.5, 0.75, 1, 0.75, 1}, 6, 0.1);
    else doneAnimation = character->getAnimation().update({0.5, 0.75, 1, 0.75, 1}, 13, 0.1);
    if(doneAnimation) character->growthUp = false;
}

void PlayerLevelAnimationManager::shrink() {
    bool doneAnimation;
    if(character->getOrientation() == LEFT) doneAnimation = character->getAnimation().update({2, 1.5, 1, 1.5, 1}, 6, 0.1);
    else doneAnimation = character->getAnimation().update({2, 1.5, 1, 1.5, 1}, 13, 0.1);
    if(doneAnimation) character->shrinkDown = false;
    return;
}

void PlayerDownPipeAnimation::initialize(Character* player) {
    this->player = player;
    targetY = player->getPos().y + player->getRectangle().height;
}

bool PlayerDownPipeAnimation::isDone() {
    return player->getPos().y >= targetY;
}
void PlayerDownPipeAnimation::update() {
    player->playerLevelAnimationManager.goDownward();
}

string PlayerDownPipeAnimation::getType() const {
    return "Down";
}

void PlayerDownPipeAnimation::saveToFile(std::ofstream& out) const {
    out << getType();
}

void PlayerIntoLeftPipeAnimation::initialize(Character* player) {
    this->player = player;
    targetX = player->getPos().x - player->getRectangle().width;
}

bool PlayerIntoLeftPipeAnimation::isDone() {
    return player->getPos().x <= targetX;
}

void PlayerIntoLeftPipeAnimation::update() {
    player->playerLevelAnimationManager.goLeftward();
}

string PlayerIntoLeftPipeAnimation::getType() const {
    return "Left";
}

void PlayerIntoLeftPipeAnimation::saveToFile(std::ofstream& out) const {
    out << getType();
}

void PlayerIntoRightPipeAnimation::initialize(Character* player) {
    this->player = player;
    targetX = player->getPos().x + player->getRectangle().width;
}

bool PlayerIntoRightPipeAnimation::isDone() {
    return player->getPos().x >= targetX;
}
    
void PlayerIntoRightPipeAnimation::update() {
    player->playerLevelAnimationManager.goRightward();
}

string PlayerIntoRightPipeAnimation::getType() const {
    return "Right";
}

void PlayerIntoRightPipeAnimation::saveToFile(std::ofstream& out) const {
    out << getType();
}

PlayerUpPipeAnimation::PlayerUpPipeAnimation(float targetY) : targetY(targetY) {}

void PlayerUpPipeAnimation::initialize(Character* player) {
    this->player = player;
}

bool PlayerUpPipeAnimation::isDone() {
    return player->getPos().y <= targetY;
}

void PlayerUpPipeAnimation::update() {
    player->playerLevelAnimationManager.goUpward();
}

string PlayerUpPipeAnimation::getType() const {
    return "Up";
}

void PlayerUpPipeAnimation::saveToFile(std::ofstream& out) const {
    out << getType() << ' ' << targetY;
}

PlayerClimbDownAnimation::PlayerClimbDownAnimation(float pivotX, float targetY) : pivotX(pivotX), targetY(targetY) {}

void PlayerClimbDownAnimation::initialize(Character* player) {
    this->player = player;
}

bool PlayerClimbDownAnimation::isDone() {
    return player->getPos().y + player->getRectangle().width >= targetY;
}

void PlayerClimbDownAnimation::update() {
    if(player->getOrientation() == LEFT) {
        player->getAnimation().update(GetFrameTime(), 14, 2);
    }
    else {
        player->getAnimation().update(GetFrameTime(), 16, 2);
    }
    player->playerLevelAnimationManager.climbDown(pivotX);
}

string PlayerClimbDownAnimation::getType() const {
    return "ClimbDown";
}

void PlayerClimbDownAnimation::saveToFile(std::ofstream& out) const {
    out << getType() << ' ' << targetY;
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
        player->playerLevelAnimationManager.goRightward();
    } else if(player->getPos().x > targetX) {
        blocks->update(player);
        player->playerLevelAnimationManager.goLeftward();
    }
}

string PlayerWalkToXAnimation::getType() const {
    return "WalkToX";
}

void PlayerWalkToXAnimation::saveToFile(std::ofstream& out) const {
    out << getType() << ' ' << targetX;
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
    player->playerLevelAnimationManager.disappear();
}

string PlayerEnterDoorAnimation::getType() const {
    return "EnterDoor";
}

void PlayerEnterDoorAnimation::saveToFile(std::ofstream& out) const {
    out << getType();
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
    player->getAnimation().update(GetFrameTime(), 6, 1);
    player->playerLevelAnimationManager.appear();
}

string PlayerExitDoorAnimation::getType() const {
    return "ExitDoor";
}

void PlayerExitDoorAnimation::saveToFile(std::ofstream& out) const {
    out << getType();
}

void PlayerGrowAnimation::initialize(Character* player) {
    this->player = player;
}

bool PlayerGrowAnimation::isDone() {
    return !player->getGrowthUp();
}

void PlayerGrowAnimation::update() {
    player->playerLevelAnimationManager.grow();
}

string PlayerGrowAnimation::getType() const {
    return "Grow";
}

void PlayerGrowAnimation::saveToFile(std::ofstream& out) const {
    out << getType();
}

void PlayerShrinkAnimation::initialize(Character* player) {
    this->player = player;
}

bool PlayerShrinkAnimation::isDone() {
    return !player->getShrinkDown();
}

void PlayerShrinkAnimation::update() {
    player->playerLevelAnimationManager.shrink();
}

string PlayerShrinkAnimation::getType() const {
    return "Shrink";
}

void PlayerShrinkAnimation::saveToFile(std::ofstream& out) const {
    out << getType();
}