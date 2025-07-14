#include"../../include/entities/Mario.hpp"

Mario::Mario() : Character() {
    sprite = LoadTexture(CharacterVar::MarioSpritePath.c_str());
    frames = CharacterSprite::Small::frames;
}

Mario::~Mario() {
    UnloadTexture(sprite);
}

CharacterType Mario::getType()const {
    return MARIO;
}