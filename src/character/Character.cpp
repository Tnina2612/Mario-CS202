#include "../../include/entities/Character.hpp"
#include "core/Program.hpp"
#include "core/SoundManager.hpp"
#include "core/MusicManager.hpp"

Character::Character() : mAnimation(CharacterSprite::Small::frames), state(nullptr), pos(CharacterVar::position), 
    invincibilityTime(0.0f), score(0), veclocityX(0.0f), veclocityY(50.0f), orientation(RIGHT), characterState(SMALL),
    isInvincible(false), isDead(false), behavior(IDLE), onGround(true), playerLevelAnimationManager(this) {
        accelerationX = 0.0f;
        accelerationY = 0.0f;
        timeEffect = 0.0f;
        onAnimation = true;
        growthUp = false;
        shrinkDown = false;
        isStarMan = false;
        isThrow = false;
        allFrames = CharacterSprite::Small::allFrames;
        effects.push_back(new Effect(0.5f, &growthUp));
        effects.push_back(new Effect(0.5f, &shrinkDown));
        effects.push_back(new Effect(0.1f, &isThrow));
        effects.push_back(new Effect(10.0f, &isStarMan));
        effects.push_back(new Effect(2.0f, &isInvicinbleBlinking));
    }

Character::Character(const vector<Rectangle>& frames, const Texture2D& sprite)
    : Character() {
    mAnimation.setFrames(frames);
    mAnimation.setSprite(sprite);
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
    if (onGround && veclocityY > restVeclocity) {
        behavior = IDLE; // Reset behavior to IDLE when landing
        veclocityX = 0.0f;
        veclocityY = restVeclocity; // Reset vertical velocity when landing
    }
    if(!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT)) {
        veclocityX = 0.0f; // Reset horizontal velocity when jumping
    }
}

Character::~Character() {
    if(state) {
        delete state;
    }
    for (auto& effect : effects) {
        if(effect) delete effect;
    }
    for (auto& fireball : fireballs) {
        if(fireball) delete fireball;
    }
    effects.clear();
}

void Character::resetAttributes() {
    onGround = false;
    collideLeft = false;
    collideRight = false;
}

void Character::handleSpriteandAllFrames() {
    if(isStarMan) {
        mAnimation.setSprite(invincibleSprite);
        if(characterState == SMALL) {
            if(getType() == MARIO) {
                allFrames = MarioInvincible::Small::allFrames;
            } else {
                allFrames = LuigiInvicinble::Small::allFrames;
            }
        }
        else {
            if(getType() == MARIO) {
                allFrames = MarioInvincible::Super::allFrames;
            } else {
                allFrames = LuigiInvicinble::Super::allFrames;
            }
        }
    }
    else {
        mAnimation.setSprite(normalSprite);
        if(characterState == SMALL) {
            allFrames = CharacterSprite::Small::allFrames;
        }
        else if(characterState == SUPER) {
            allFrames = CharacterSprite::Super::allFrames;
        }
        else if(characterState == FIRE) {
            allFrames = CharacterSprite::Fire::allFrames;
        }
    }
}

void Character::update() {
    float deltaTime = GetFrameTime();
    debug();
    handleEffect();
    handleFireballEffect();                         //< bug cause crash: FIXED
    handleSpriteandAllFrames();
    handleInvincinbleTime(deltaTime);
    // if(growthUp) {
    //     bool doneAnimation;
    //     if(orientation == LEFT) doneAnimation = mAnimation.update({0.5, 0.75, 1, 0.75, 1}, 6, 0.1);
    //     else doneAnimation = mAnimation.update({0.5, 0.75, 1, 0.75, 1}, 13, 0.1);
    //     if(doneAnimation) growthUp = false;
    //     return;
    // }
    // if(shrinkDown) {
    //     bool doneAnimation;
    //     if(orientation == LEFT) doneAnimation = mAnimation.update({2, 1.5, 1, 1.5, 1}, 6, 0.1);
    //     else doneAnimation = mAnimation.update({2, 1.5, 1, 1.5, 1}, 13, 0.1);
    //     if(doneAnimation) {
    //         shrinkDown = false;
    //     }
    //     return;
    // }
    if(isThrow) {
        if(orientation == LEFT) {
            mAnimation.setFrames(allFrames["LThrow"]);
        }
        else {
            mAnimation.setFrames(allFrames["RThrow"]);
        }
        mAnimation.update(deltaTime);
        return;
    }
    // if(isInvicinbleBlinking) {
    //     mAnimation.updateBlinking(deltaTime, onAnimation);
    // }
    // if(invincibilityTime > 0.0f && !isStarMan) {
    //     invincibilityTime -= deltaTime;
    //     if(invincibilityTime <= 0.0f) {
    //         isInvincible = false;
    //     }
    //     cout << "Invincibility time left: " << invincibilityTime << endl;
    // }
    // else {
    //     isInvincible = false;
    // }
    switch (behavior) {
        case MOVE:
            if (orientation == RIGHT) {
                moveRight();
                mAnimation.setFrames(allFrames["RRun"]);
            } 
            else if (orientation == LEFT) {
                moveLeft();
                mAnimation.setFrames(allFrames["LRun"]);
            }
            break;
        case JUMP:
            jump();
            if (orientation == RIGHT) {
                mAnimation.setFrames(allFrames["RJump"]);
            } 
            else if (orientation == LEFT) {
                mAnimation.setFrames(allFrames["LJump"]);
            }
            break;
        case DUCK:
            if (orientation == LEFT) {
                mAnimation.setFrames(allFrames["LDuck"]);
            } 
            else if (orientation == RIGHT) {
                mAnimation.setFrames(allFrames["RDuck"]);
            }           
            break;
        case IDLE:
            accelerationX = 0.0f; // Reset acceleration when idle
            if (orientation == LEFT) {
                mAnimation.setFrames(allFrames["LIdle"]);
            } 
            else if (orientation == RIGHT) {
                mAnimation.setFrames(allFrames["RIdle"]);
            }
            break;
        case BRAKE:
            if (orientation == RIGHT) {
                brakeRight();
                mAnimation.setFrames(allFrames["RBrake"]);
            } 
            else if (orientation == LEFT) {
                brakeLeft();
                mAnimation.setFrames(allFrames["LBrake"]);
            }
            break;
        case THROW:
            // Handle THROW behavior here
            break;
        case DEAD:
            veclocityX = 0.0f;
            // Nếu muốn Mario rơi xuống khi chết:
            characterState = SMALL;
            mAnimation.setFrames(allFrames["Duck"]);
            // Có thể thêm điều kiện để reset game hoặc respawn ở đây
            break;
        case CLIMB:
            if(orientation == LEFT) {
                mAnimation.setFrames(allFrames["LClimb"]);
            }
            else {
                mAnimation.setFrames(allFrames["RClimb"]);
            }
            break;
        default:
            break;
    }
    mAnimation.update(deltaTime);
}

void Character::draw() {
    if(!onAnimation && isInvicinbleBlinking) return;
    mAnimation.draw({pos.x, pos.y - mAnimation.getCurrentRectangle().height * mAnimation.getScale()});
    for (auto& fireball : fireballs) {
        if(fireball && fireball->getOnScreen()) {
            fireball->draw();
        }
    }
}

void Character::debug() {
    if(IsKeyPressed(KEY_W)) {
        if(getCharacterState() == CharacterState::SMALL) {
            characterState = CharacterState::SUPER;
            allFrames = CharacterSprite::Super::allFrames;
            growthUp = true;
        } else if(getCharacterState() == CharacterState::SUPER) {
            characterState = CharacterState::FIRE;
            allFrames = CharacterSprite::Fire::allFrames;
        } else if(getCharacterState() == CharacterState::FIRE) {
            characterState = CharacterState::SMALL;
            allFrames = CharacterSprite::Small::allFrames;
            shrinkDown = true;
        }
    }
    if(IsKeyPressed(KEY_S)) {
        isStarMan = true;
        isInvincible = true;
    }
}

void Character::setBehavior(Behavior newBehavior) {
    behavior = newBehavior;
}

void Character::powerUp() {
    Program::getInstance().getHUD().onNotify(EventType::ADDSCORE, pos);
    if(getCharacterState() == CharacterState::SMALL) {
        characterState = CharacterState::SUPER;
        allFrames = CharacterSprite::Super::allFrames;
        growthUp = true;
        SoundManager::getInstance().playSound(SoundType::POWERUP);
    } else if(getCharacterState() == CharacterState::SUPER) {
        characterState = CharacterState::FIRE;
        allFrames = CharacterSprite::Fire::allFrames;
    }
}

bool Character::getGrowthUp() const {
    return growthUp;
}

bool Character::getShrinkDown() const {
    return shrinkDown;
}

void Character::createFireball() {
    if(getCharacterState() == CharacterState::FIRE) {
        isThrow = true;
        Vector2 startPos = {pos.x + getRectangle().width, pos.y - getRectangle().height / 2};
        fireballs.push_back(new CharacterFireball(startPos, orientation));
    }
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
    float width, height;
    if(characterState == SMALL) {
        width = 14;
        height = 15;
    }
    else {
        width = 14;
        if(behavior != DUCK) height = 31;
        else height = 15; // If ducking, height is smaller
    }
    return Rectangle{pos.x, pos.y - height, /*frames[currentFrame].width * scale*/width, height};
}

CharacterState Character::getCharacterState() const {
    return characterState;
}

Animation& Character::getAnimation() {
    return mAnimation;
}

void Character::hitBlockLeft() {
    //pos.x = vline;
    veclocityX = 0.0f; // Stop moving left
    collideLeft = true;
}

void Character::hitBlockRight() {
    //pos.x = vline - getRectangle().width;
    veclocityX = 0.0f; // Stop moving right
    collideRight = true;
}

void Character::hitBlockTop() {
    veclocityY = 0; // Reset vertical velocity when hitting a block from the top
}

void Character::hitBlockBottom() {
    // if(IsKeyDown(KEY_LEFT) == false && IsKeyDown(KEY_RIGHT) == false) {
    //     setBehavior(IDLE);
    // }
    // else {
    //     setBehavior(MOVE);
    // }
    onGround = true;
    if(!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN) && behavior != BRAKE) {
        behavior = IDLE;
    }
    veclocityY = restVeclocity; // Reset vertical velocity when hitting a block from the bottom
}

void Character::die() {
    behavior = DEAD;
    isDead = true;
    veclocityX = 0.0f;
    veclocityY = -jumpVeclocity; // Mario sẽ bật lên một chút khi chết (tùy chọn)
    onGround = false;

    Program::getInstance().getHUD().onNotify(EventType::MARIO_DIED);
    MusicManager::getInstance().stopMusic();
    SoundManager::getInstance().playSound(SoundType::MARIO_DIE);
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

void Character::handleEffect(float deltaTime) {
    for(auto& effect : effects) {
        if(effect) {
            effect->handleEffect(deltaTime);
        }
    }
}

Vector2 Character::getPos() const {
    return pos;
}

bool Character::getIsDead() const {
    return this->isDead;
}

void Character::handleFireballEffect(float deltaTime) {
    // for(auto& fireball : fireballs) {
    //     if(!fireball) {
    //         fireballs.erase(remove(fireballs.begin(), fireballs.end(), fireball), fireballs.end());
    //     }
    //     else if(fireball->getOnScreen() == false) {
    //         delete fireball;
    //         fireball = nullptr;
    //         fireballs.erase(remove(fireballs.begin(), fireballs.end(), fireball), fireballs.end());
    //     }
    // }

    // Fix bug erasing inside a range-based for loop
    for (auto& fireball : fireballs) {
        if (fireball && !fireball->getOnScreen()) {
            delete fireball;
            fireball = nullptr;
        }
    }

    fireballs.erase(
        std::remove(fireballs.begin(), fireballs.end(), nullptr),
        fireballs.end()
    );
}

void Character::handleInvincinbleTime(float deltaTime) {
    if(isInvicinbleBlinking) {
        mAnimation.updateBlinking(deltaTime, onAnimation);
    }
    if(invincibilityTime > 0.0f) {
        invincibilityTime -= deltaTime;
        if(invincibilityTime <= 0.0f) {
            isInvincible = false;
        }
        cout << "Invincibility time left: " << invincibilityTime << endl;
    }
    else {
        isInvincible = false;
    }
    if(isStarMan) {
        isInvincible = true; 
    }
}

vector<CharacterFireball*>& Character::getFireballs() {
    return fireballs;
}

void Character::takeDamage() {
    if(isInvincible || isDead) return; // Ignore damage if invincible or dead
    if(characterState == SMALL) {
        die(); // If Mario is small, he dies
        return;
    }
    shrinkDown = true; // Trigger shrink down effect
    isInvincible = true; // Set invincibility
    characterState = SMALL;
    allFrames = CharacterSprite::Small::allFrames; // Reset to small frames
    SoundManager::getInstance().playSound(SoundType::POWERDOWN);
}

void Character::addCoin() {
    SoundManager::getInstance().playSound(SoundType::COIN);
    Program::getInstance().getHUD().onNotify(EventType::ADDSCORE, pos);
    Program::getInstance().getHUD().onNotify(EventType::COLLECT_COINS, pos);
}

void Character::addLife() {
    SoundManager::getInstance().playSound(SoundType::ONE_UP);
    Program::getInstance().getHUD().onNotify(EventType::ADDSCORE, pos);
    Program::getInstance().getHUD().onNotify(EventType::ADDLIVES, pos);
}