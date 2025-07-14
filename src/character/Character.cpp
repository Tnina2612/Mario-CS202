#include"../../include/entities/Character.hpp"

Character::Character() : state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f), orientation(RIGHT), characterState(SMALL),
    isMove(false), isJump(false), isBrake(false), isDuck(false), isThrow(false), isInvincible(false), isDead(false) {}

Character::Character(const vector<Rectangle>& frames, const Texture2D& sprite)
    : Animation(frames, sprite), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f), orientation(RIGHT), characterState(SMALL),
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
void Character::update() {
    if(IsKeyDown(KEY_RIGHT)) {
        if(IsKeyDown(KEY_UP)) {
            isMove = false;
            isJump = true;
            orientation = RIGHT;
        }
        else isJump = false;
        isMove = true;
    }
    if(IsKeyDown(KEY_LEFT)) {
        if(IsKeyDown(KEY_UP)) {
            isMove = false;
            isJump = true;
            orientation = LEFT;
        }
        else isJump = false;
        isMove = true;
    }
    if(isMove) {
        if (orientation == RIGHT) {
            Animation::update(GetFrameTime(), 10, 3);
        }
        else if (orientation == LEFT) {
            Animation::update(GetFrameTime(), 3, 3);
        }
    }
    else if (isJump) {
        if(orientation == RIGHT) {
            Animation::update(GetFrameTime(), 8, 1);
        }
        else if (orientation == LEFT) {
            Animation::update(GetFrameTime(), 1, 1);
        }
    }
    else if(isDead || isDuck) {
        if(orientation ==  LEFT) {
            Animation::update(GetFrameTime(), 0, 1);
        }
        else if (orientation == RIGHT) {
            Animation::update(GetFrameTime(), 7, 1);
        }
    }
    else if(isBrake) {
        if(orientation == RIGHT) {
            Animation::update(GetFrameTime(), 9, 1);
        }
        else if (orientation == LEFT) {
            Animation::update(GetFrameTime(), 2, 1);
        }
    }
}

void Character::draw() {
    Animation::draw(pos);
}