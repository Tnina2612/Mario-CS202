#include "../../include/entities/Character.hpp"
#include "core/SoundManager.hpp"
#include "core/MusicManager.hpp"

Character::Character() : Animation(CharacterSprite::Fire::frames), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(50.0f), orientation(RIGHT), characterState(SMALL),
    isInvincible(false), isDead(false), behavior(IDLE), onGround(true) {
        accelerationX = 0.0f;
        accelerationY = 0.0f;
    }

Character::Character(const vector<Rectangle>& frames, const Texture2D& sprite)
    : Animation(frames, sprite), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(50.0f), orientation(RIGHT), characterState(SMALL),
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
    if((behavior == IDLE || behavior == MOVE) && behavior != BRAKE && behavior != DUCK &&
    collideLeft == false) {
        //if(onGround) orientation = LEFT; // Change orientation to LEFT when moving left
        veclocityX = -maxVeclocityX; // Set velocity to move left
    }
    if (!onGround && collideLeft == false) veclocityX = -maxVeclocityX; // Maintain left velocity when not on ground
}

void Character::moveRight() {
    if((behavior == IDLE || behavior == MOVE) && behavior != BRAKE && behavior != DUCK &&
    collideRight == false) {
        //if(onGround) orientation = RIGHT; // Change orientation to RIGHT when moving right
        veclocityX = maxVeclocityX; // Set velocity to move right
    }
    if (!onGround && collideRight == false) veclocityX = maxVeclocityX;
}

void Character::brakeLeft() {
    accelerationX = brakeAcceleration; // Apply left brake acceleration
    veclocityX += accelerationX * GetFrameTime();
    if(abs(veclocityX) <= 3) {
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
    veclocityX += accelerationX * GetFrameTime();
    if(abs(veclocityX) <= 3) {
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
    if (onGround && veclocityY > restVeclocity) {
        behavior = IDLE; // Reset behavior to IDLE when landing
        veclocityY = restVeclocity; // Reset vertical velocity when landing
    }
}

Character::~Character() {
    if(state) {
        delete state;
    }
}

void Character::resetAttributes() {
    onGround = false;
    collideLeft = false;
    collideRight = false;
}

void Character::update() {
    if(!onGround) {
        behavior = JUMP;
    }
    else if(behavior != BRAKE){
        if(IsKeyDown(KEY_LEFT) == false && IsKeyDown(KEY_RIGHT) == false) {
            setBehavior(IDLE);
            }
            else {
                setBehavior(MOVE);
            }
    }
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
            accelerationX = 0.0f; // Reset acceleration when idle
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
        case DEAD:
            veclocityX = 0.0f;
            // Nếu muốn Mario rơi xuống khi chết:
            characterState = SMALL;
            Animation::update(GetFrameTime(), 0, 1);
            // Có thể thêm điều kiện để reset game hoặc respawn ở đây
            break;
        default:
            break;
    }
    // veclocityX += accelerationX * GetFrameTime(); // Update horizontal velocity with acceleration
    // if(!onGround) veclocityY += gravity * GetFrameTime(); // Apply gravity if not on ground
    // cout << "Before addition: " << pos.x << ", " << pos.y << '\n';
    // cout << "Velocity, acceleration: " << veclocityX << ' ' << accelerationX << '\n';
    // pos.x = pos.x + veclocityX * GetFrameTime();
    // pos.y = pos.y + veclocityY * GetFrameTime();
    // cout << "After addition: " << pos.x << ", " << pos.y << '\n';
    // cout << "on ground" << onGround << endl;
    // cout << "veclocity X: " << veclocityX <<  endl;
    // cout << "is Brake: " << (behavior == BRAKE) << endl;
}

void Character::draw() {
    Animation::draw({pos.x, pos.y - getRectangle().height});
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
    float width;
    if(characterState == SMALL) width = 14;
    else {
        width = 16;
    }
    return Rectangle{pos.x, pos.y - frames[currentFrame].height * scale, /*frames[currentFrame].width * scale*/width, frames[currentFrame].height * scale};
}

CharacterState Character::getCharacterState() const {
    return characterState;
}

void Character::hitBlockLeft(float vline) {
    //pos.x = vline;
    veclocityX = 0.0f; // Stop moving left
    collideLeft = true;
}

void Character::hitBlockRight(float vline) {
    //pos.x = vline - getRectangle().width;
    veclocityX = 0.0f; // Stop moving right
    collideRight = true;
}

void Character::hitBlockTop(float hline) {
    veclocityY = abs(veclocityY); // Reset vertical velocity when hitting a block from the top
}

void Character::hitBlockBottom(float hline) {
    // if(IsKeyDown(KEY_LEFT) == false && IsKeyDown(KEY_RIGHT) == false) {
    //     setBehavior(IDLE);
    // }
    // else {
    //     setBehavior(MOVE);
    // }
    onGround = true;
    veclocityY = restVeclocity; // Reset vertical velocity when hitting a block from the bottom
}

void Character::die() {
    behavior = DEAD;
    isDead = true;
    veclocityX = 0.0f;
    veclocityY = -jumpVeclocity; // Mario sẽ bật lên một chút khi chết (tùy chọn)
    onGround = false;
}
bool Character::getCollideRight()const {
    return collideRight;
}
bool Character::getCollideLeft()const {
    return collideLeft;
}
// bool Character::getCollideUp()const {
    
// }
// bool Character::getCollideDown()const {

// }

float Character::getVeclocityX()const {
    return veclocityX;
}
float Character::getVeclocityY()const {
    return veclocityY;
}
void Character::setPosition(float x, float y) {
    pos.x = x; pos.y = y;
}

float Character::getGravity()const {
    return gravity;
}

float Character::getRestVeclocity()const {
    return restVeclocity;
}