#include"../../include/entities/Mario.hpp"

Mario::Mario() : Character() {
    normalSprite = Sprite::MarioSprite;
    invincibleSprite = Sprite::MarioInvincibleSprite;
    mAnimation.setSprite(normalSprite);
    allFrames = CharacterSprite::Small::allFrames;
}

Mario::~Mario() {

}

CharacterType Mario::getType()const {
    return MARIO;
}