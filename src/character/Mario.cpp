#include"../../include/entities/Mario.hpp"

Mario::Mario() : Character() {
    normalSprite = Sprite::MarioSprite;
    invincibleSprite = Sprite::MarioInvincibleSprite;
    mAnimation.setSprite(normalSprite);
    allFrames = CharacterSprite::Small::allFrames;
}

Mario::Mario(const Mario& o) : Character() {
    normalSprite = o.normalSprite;
    invincibleSprite = o.invincibleSprite;
    mAnimation.setSprite(normalSprite);
    allFrames = o.allFrames;
}

Mario::~Mario() {

}

CharacterType Mario::getType()const {
    return MARIO;
}

shared_ptr<Character> Mario::clone() const {
    return make_shared<Mario>(*this);
}