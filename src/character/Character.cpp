#include"../../include/entities/Character.hpp"

Character::Character() : Animation(CharacterSprite::Small::frames), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f), orientation(RIGHT), characterState(SMALL),
    isInvincible(false), isDead(false), behavior(IDLE) {}

Character::Character(const vector<Rectangle>& frames, const Texture2D& sprite)
    : Animation(frames, sprite), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f), orientation(RIGHT), characterState(SMALL),
    isInvincible(false), isDead(false),behavior(IDLE) {}

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
            behavior = JUMP;
        }
        else behavior = MOVE;
        orientation = RIGHT;
        moveRight();
    }
    else if(IsKeyDown(KEY_LEFT)) {
        if(IsKeyDown(KEY_UP)) {
            behavior = JUMP;
        }
        else behavior = MOVE;
        orientation = LEFT;
        moveLeft();
    }
    else {
        behavior = IDLE;
        veclocityX = 0.0f;
    }
    switch (behavior) {
        case MOVE:
            if (orientation == RIGHT) {
                Animation::update(GetFrameTime(), 10, 3);
            } 
            else if (orientation == LEFT) {
                Animation::update(GetFrameTime(), 3, 3);
            }
            break;
        case JUMP:
            if (orientation == RIGHT) {
                Animation::update(GetFrameTime(), 8, 1);
            } 
            else if (orientation == LEFT) {
                Animation::update(GetFrameTime(), 1, 1);
            }
            break;
        case DUCK:
            if (orientation == LEFT) {
                Animation::update(GetFrameTime(), 0, 1);
            } 
            else if (orientation == RIGHT) {
                Animation::update(GetFrameTime(), 7, 1);
            }           
            break;
        case IDLE:
            if (orientation == LEFT) {
                Animation::update(GetFrameTime(), 6, 1);
            } 
            else if (orientation == RIGHT) {
                Animation::update(GetFrameTime(), 13, 1);
            }
            break;
        case BRAKE:
            if (orientation == RIGHT) {
                Animation::update(GetFrameTime(), 9, 1);
            } 
            else if (orientation == LEFT) {
                Animation::update(GetFrameTime(), 2, 1);
            }
            break;
        case THROW:
            // Handle THROW behavior here
            break;
        default:
            break;
    }
    pos.x = pos.x + veclocityX * GetFrameTime();
    pos.y = pos.y + veclocityY * GetFrameTime();
}

void Character::draw() {
    Animation::draw(pos);
}