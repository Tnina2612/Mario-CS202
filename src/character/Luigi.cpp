#include"../../include/entities/Luigi.hpp"

Luigi::Luigi() : Character() {
    normalSprite = Sprite::LuigiSprite;
    invincibleSprite = Sprite::LuigiInvincibleSprite;
    mAnimation.setSprite(normalSprite);
    allFrames = CharacterSprite::Small::allFrames;
}

Luigi::~Luigi() {

}

CharacterType Luigi::getType()const {
    return LUIGI;
}