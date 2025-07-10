#include"../../include/entities/Character.hpp"

Character::Character() : state(nullptr), pos(CharacterVar::position), invincibilityTime(0.0f), lives(3), score(0), veclocityX(0.0f), veclocityY(0.0f) {}

Character::Character(const string& spritePath) : Character() {
    // load sprite of character
    sprite = LoadTexture(spritePath.c_str());
}

void Character::setState(IState* newState) {
    if(state) {
        delete state; // clean up old state
    }
    state = newState;
}

void Character::moveLeft() {
    pos.x -= veclocityX * GetFrameTime();
}

void Character::moveRight() {
    pos.x += veclocityX * GetFrameTime();
}

Character::~Character() {
    if(state) {
        delete state;
    }
    UnloadTexture(sprite);
}