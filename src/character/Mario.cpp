#include"../../include/entities/Mario.hpp"

Mario::Mario() : Character() {
    sprite = LoadTexture(CharacterVar::MarioSpritePath.c_str());
    frames = CharacterSprite::Super::frames; // Use Fire frames for Mario
}

Mario::~Mario() {
    UnloadTexture(sprite);
}

CharacterType Mario::getType()const {
    return MARIO;
}

Vector2 Character::getPos() const {
    return pos;
}