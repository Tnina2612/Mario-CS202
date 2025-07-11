#include"../../include/entities/Character.hpp"

Character::Character() : state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f), orientation(RIGHT),
    isMove(false), isJump(false), isBrake(false), isDuck(false), isThrow(false), isInvincible(false), isDead(false) {

    }

Character::Character(const vector<Rectangle>& frames, const Texture2D& sprite)
    : Animation(frames, sprite), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f), orientation(RIGHT),
    isMove(false), isJump(false), isBrake(false), isDuck(false), isThrow(false), isInvincible(false), isDead(false) {}

void Character::setState(IState* newState) {
    if(state) {
        delete state; // clean up old state
    }
    state = newState;
}

void Character::moveLeft() {
    veclocityX = -maxVeclocityX; // Set velocity to move left

}

void Character::moveRight() {
    veclocityX = maxVeclocityX; // Set velocity to move right
}

Character::~Character() {
    if(state) {
        delete state;
    }
}