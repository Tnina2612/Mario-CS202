#include"../../include/entities/Mario.hpp"

Mario::Mario() : Character() {
    mAnimation.setSprite(Sprite::MarioSprite);
}

Mario::~Mario() {

}

CharacterType Mario::getType()const {
    return MARIO;
}

Vector2 Character::getPos() const {
    return pos;
}

bool Character::getIsDead() const {
    return this->isDead;
}