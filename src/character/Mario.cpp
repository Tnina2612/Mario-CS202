#include"../../include/entities/Mario.hpp"

Mario::Mario() : Character() {
    mAnimation.setSprite(Sprite::MarioSprite);
}

Mario::~Mario() {

}

CharacterType Mario::getType()const {
    return MARIO;
}