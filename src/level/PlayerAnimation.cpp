#include<entities/PlayerAnimation.hpp>
#include<core/Program.hpp>
#include<scenes/TitleScene.hpp>

PlayerLevelAnimationManager::PlayerLevelAnimationManager(Character* character) : character(character) {
}

void PlayerLevelAnimationManager::goDownward() {
    float x = character->getPos().x;
    float y = character->getPos().y + GetFrameTime() * LevelVar::animationSpeed;
    character->setPosition(x, y);
}

void PlayerLevelAnimationManager::goLeftward() {
    float x = character->getPos().x - GetFrameTime() * LevelVar::animationSpeed;
    float y = character->getPos().y;
    character->setPosition(x, y);
}

void PlayerLevelAnimationManager::goRightward() {
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
    if(character->getOrientation() == LEFT) {
        character->getAnimation().setFrames(character->allFrames["LClimb"]);
    } else {
        character->getAnimation().setFrames(character->allFrames["RClimb"]);
    }
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
    if(character->getOrientation() == LEFT) {
        character->getAnimation().setFrames(character->allFrames["LIdle"]);
    }
    else {
        character->getAnimation().setFrames(character->allFrames["RIdle"]);
    }
    doneAnimation = character->getAnimation().update({0.5, 0.75, 1, 0.75, 1}, 0, 0.1);
    if(doneAnimation) character->growthUp = false;
}

void PlayerLevelAnimationManager::shrink() {
    bool doneAnimation;
    if(character->getOrientation() == LEFT) {
        character->getAnimation().setFrames(character->allFrames["LIdle"]);
    }
    else {
        character->getAnimation().setFrames(character->allFrames["RIdle"]);
    }
    doneAnimation = character->getAnimation().update({2, 1.5, 1, 1.5, 1}, 0, 0.1);
    if(doneAnimation) {
        character->shrinkDown = false;
        character->isInvicinbleBlinking = true;
        character->invincibilityTime = 2.0f; // Set invincibility time
    }
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

PlayerClimbDownFlagColumnAnimation::PlayerClimbDownFlagColumnAnimation(float pivotX, float targetY, bool directionAfterClimbIsRight) : 
    pivotX(pivotX), targetY(targetY), directionAfterClimbIsRight(directionAfterClimbIsRight) 
{
    // Constructor
}

void PlayerClimbDownFlagColumnAnimation::initialize(Character* player) {
    this->player = player;
    elapsedTime = 0.f;
}

bool PlayerClimbDownFlagColumnAnimation::isDone() {
    return (player->getPos().y >= targetY && player->getOrientation() == directionAfterClimbIsRight && elapsedTime >= waitTime);
}

void PlayerClimbDownFlagColumnAnimation::update() {
    if(player->getPos().y >= targetY) {
        player->setPosition(player->getPos().x, targetY);
        player->setOrientation(directionAfterClimbIsRight ? RIGHT : LEFT);
        player->getAnimation().setFrames({player->allFrames[directionAfterClimbIsRight ? "RClimb" : "LClimb"]
            [player->getCharacterState() == CharacterState::SMALL ? 1 : 0]});

        elapsedTime += GetFrameTime();
    } else {
        player->playerLevelAnimationManager.climbDown(pivotX);
    }
    player->getAnimation().update(GetFrameTime());
}

string PlayerClimbDownFlagColumnAnimation::getType() const {
    return "ClimbDown";
}

void PlayerClimbDownFlagColumnAnimation::saveToFile(std::ofstream& out) const {
    out << getType() << ' ' << targetY << ' ' << directionAfterClimbIsRight;
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
        player->getAnimation().setFrames(player->allFrames["RRun"]);
    } else if(player->getPos().x > targetX) {
        blocks->update(player);
        player->playerLevelAnimationManager.goLeftward();
        player->getAnimation().setFrames(player->allFrames["LRun"]);
    }
    player->getAnimation().update(GetFrameTime());
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

PlayerWaitAnimation::PlayerWaitAnimation(float waitTime) : waitTime(waitTime) {}

void PlayerWaitAnimation::initialize(Character* player) {
    this->player = player;
    this->elapsedTime = 0.f;
}

bool PlayerWaitAnimation::isDone() {
    return elapsedTime >= waitTime;
}

void PlayerWaitAnimation::update() {
    elapsedTime += GetFrameTime();
}

string PlayerWaitAnimation::getType() const {
    return "Wait";
}

void PlayerWaitAnimation::saveToFile(std::ofstream& out) const {
    out << getType() << " " << waitTime;
}

PlayerWinAnimation::PlayerWinAnimation() : waitTime(1.f) {}

void PlayerWinAnimation::initialize(Character* player) {
    this->player = player;
    printText1 = printText2 = false;
}

bool PlayerWinAnimation::isDone() {
    elapsedTime += GetFrameTime();

    if(printText1 == false) {
        if(elapsedTime >= waitTime) {
            elapsedTime = 0;
            Program::getInstance().getHUD().addLevelAnnouncement("YOU WIN!");
            printText1 = true;
        }
    } else if(printText2 == false) {
        if(elapsedTime >= waitTime) {
            elapsedTime = 0;
            Program::getInstance().getHUD().addLevelAnnouncement("PRESS [ENTER] TO CONTINUE");
            printText2 = true;
        }
    } else {
        if(IsKeyPressed(KEY_ENTER)) {
            Program::getInstance().getHUD().clearLevelAnnouncement();
            Program::getInstance().pushScene(new TitleScene());
            return true;
        }
    }

    return false;
}

void PlayerWinAnimation::update() {
    
}

string PlayerWinAnimation::getType() const {
    return "Win";
}

void PlayerWinAnimation::saveToFile(std::ofstream& out) const {
    out << getType();
}