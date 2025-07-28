#include"../../include/entities/Character.hpp"

Character::Character() : Animation(CharacterSprite::Fire::frames), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f), orientation(RIGHT), characterState(SMALL),
    isInvincible(false), isDead(false), behavior(IDLE), onGround(true) {
        accelerationX = 0.0f;
        accelerationY = 0.0f;
    }

Character::Character(const vector<Rectangle>& frames, const Texture2D& sprite)
    : Animation(frames, sprite), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f), orientation(RIGHT), characterState(SMALL),
    isInvincible(false), isDead(false),behavior(IDLE), onGround(true) {
        accelerationX = 0.0f;
        accelerationY = 0.0f;
    }

void Character::setState(IState* newState) {
    if(state) {
        delete state; // clean up old state
    }
    state = newState;
}

void Character::moveLeft() {
    if((behavior == IDLE || behavior == MOVE) && behavior != BRAKE && behavior != DUCK) {
        //if(onGround) orientation = LEFT; // Change orientation to LEFT when moving left
        veclocityX = -maxVeclocityX; // Set velocity to move left
    }
    if (!onGround) veclocityX = -maxVeclocityX; // Maintain left velocity when not on ground
}

void Character::moveRight() {
    if((behavior == IDLE || behavior == MOVE) && behavior != BRAKE && behavior != DUCK) {
        //if(onGround) orientation = RIGHT; // Change orientation to RIGHT when moving right
        veclocityX = maxVeclocityX; // Set velocity to move right
    }
    if (!onGround) veclocityX = maxVeclocityX;
}

void Character::brakeLeft() {
    accelerationX = brakeAcceleration; // Apply left brake acceleration
    if(abs(veclocityX) <= 5) {
        behavior = IDLE;
        veclocityX = 0.0f; // Stop moving left
        accelerationX = 0.0f; // Reset acceleration
        if(IsKeyDown(KEY_RIGHT)) {
            behavior = MOVE; // If right key is pressed, switch to MOVE
            orientation = RIGHT; // Change orientation to RIGHT
        }
    }
}

void Character::brakeRight() {
    accelerationX = -brakeAcceleration;
    if(abs(veclocityX) <= 5) {
        behavior = IDLE;
        veclocityX = 0.0f; // Stop moving right
        accelerationX = 0.0f; // Reset acceleration
        if(IsKeyDown(KEY_LEFT)) {
            behavior = MOVE; // If left key is pressed, switch to MOVE
            orientation = LEFT; // Change orientation to LEFT
        }
    }
}

void Character::jump() {
    if(IsKeyReleased(KEY_UP)) {
        veclocityY = veclocityY * 0.5f;
    }
    if(!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
        veclocityX = 0.0f; // Reset horizontal velocity when jumping
    }
    if (pos.y > CharacterVar::position.y) {
        pos.y = CharacterVar::position.y; // Reset position to initial y if it goes below
        onGround = true; // Set onGround to true when landing
        behavior = IDLE; // Reset behavior to IDLE when landing
        veclocityY = 0.0f; // Reset vertical velocity when landing
    }
}

Character::~Character() {
    if(state) {
        delete state;
    }
}


void Character::update() {
    switch (behavior) {
        case MOVE:
            if (orientation == RIGHT) {
                moveRight();
                Animation::update(GetFrameTime(), 10, 3);
            } 
            else if (orientation == LEFT) {
                moveLeft();
                Animation::update(GetFrameTime(), 3, 3);
            }
            break;
        case JUMP:
            jump();
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
                brakeRight();
                Animation::update(GetFrameTime(), 9, 1);
            } 
            else if (orientation == LEFT) {
                brakeLeft();
                Animation::update(GetFrameTime(), 2, 1);
            }
            break;
        case THROW:
            // Handle THROW behavior here
            break;
        default:
            break;
    }
    veclocityX += accelerationX * GetFrameTime(); // Update horizontal velocity with acceleration
    if(!onGround) veclocityY += gravity * GetFrameTime(); // Apply gravity if not on ground
    pos.x = pos.x + veclocityX * GetFrameTime();
    pos.y = pos.y + veclocityY * GetFrameTime();
}

void Character::draw() {
    Animation::draw(pos);
}

void Character::setBehavior(Behavior newBehavior) {
    behavior = newBehavior;
}

Behavior Character::getBehavior() const {
    return behavior;
}

void Character::setOrientation(Orientation newOrientation) {
    orientation = newOrientation;
}

Orientation Character::getOrientation() const {
    return orientation;
}

bool Character::getOnGround() const {
    return onGround;
}

void Character::setOnGround(bool onGround) {
    this->onGround = onGround;
}

void Character::setVelocityX(float velocity) {
    veclocityX = velocity;
}

void Character::setVeclocityY(float velocity) {
    veclocityY = velocity;
}

float Character::getJumpVelocity() const {
    return jumpVeclocity;
}

Rectangle Character::getRectangle() const {
    return Rectangle{pos.x, pos.y, sprite.width * scale, sprite.height * scale};
}

CharacterState Character::getCharacterState() const {
    return characterState;
}

void Character::hitBlockLeft() {
    behavior = IDLE;
    veclocityX = 0.0f; // Stop moving left
}

void Character::hitBlockRight() {
    behavior = IDLE;
    veclocityX = 0.0f; // Stop moving right
}

void Character::hitBlockTop() {
    veclocityY = -veclocityY; // Reset vertical velocity when hitting a block from the top
}

void Character::hitBlockBottom() {
    onGround = true; // Set onGround to true when hitting a block from the bottom
    veclocityY = 0.0f; // Reset vertical velocity when hitting a block from the bottom
}

