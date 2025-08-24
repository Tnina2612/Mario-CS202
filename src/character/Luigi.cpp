#include"../../include/entities/Luigi.hpp"

Luigi::Luigi() : Character() {
    normalSprite = Sprite::LuigiSprite;
    invincibleSprite = Sprite::LuigiInvincibleSprite;
    mAnimation.setSprite(normalSprite);
    allFrames = CharacterSprite::Small::allFrames;
}

Luigi::Luigi(const Luigi& o) : Character() {
    normalSprite = o.normalSprite;
    invincibleSprite = o.invincibleSprite;
    mAnimation.setSprite(normalSprite);
    allFrames = o.allFrames;
}

Luigi::~Luigi() {

}

CharacterType Luigi::getType()const {
    return LUIGI;
}

shared_ptr<Character> Luigi::clone() const {
    return make_shared<Luigi>(*this);
}