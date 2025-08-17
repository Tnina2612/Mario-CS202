#include<cmath>
#include<iostream>

#include"../../include/entities/Enemy/CharacterFireball.hpp"
#include"../../include/entities/Enemy/EnemyFactory.hpp"

CharacterFireball::CharacterFireball() : bombEffect() {
    allFrames = CharacterSprite::Fire::FireballSprite::Frames;
    m_animation.setSprite(EnemyFactory::getEnemyTypes()->sprite);
    m_animation.setFrames(allFrames["Normal"]);
}

CharacterFireball::CharacterFireball(Vector2 startPos, Orientation orientation) : CharacterFireball() {
    _width = 10.f;
    _height = 10.f;
    _pos = startPos;
    _active = true;
    _onScreen = true;
    this->orientation = orientation;
    bombEffect.addEffect(0.3f, &_onScreen);
    float velocityX = 300.0f;
    if(orientation == LEFT) {
        _velocity.x = -velocityX;
    }
    else {
        _velocity.x = velocityX;
    }
    _velocity.y = 100.0f;
}

Rectangle CharacterFireball::getHitBox() {
    return Rectangle{_pos.x, _pos.y, _width, _height};
}

void CharacterFireball::update(float dt) {
    _velocity.y += gravity * dt; // Apply 
    if(!_active) {
        bombEffect.handleEffect(dt);
    }
    if(_velocity.y > 2 * _velocity_y) {
        _velocity.y = 2 * _velocity_y; // Limit the maximum downward velocity
    }
    else if(_velocity.y < -_velocity_y) {
        _velocity.y = -_velocity_y; // Limit the maximum upward velocity
    }
    m_animation.update(dt);

}

void CharacterFireball::draw() {
    m_animation.draw(_pos);
}
bool CharacterFireball::getOnScreen() const {
    return _onScreen;
}

bool CharacterFireball::getActive()const {
    return _active;
}

Vector2 CharacterFireball::getVelocity() const {
    return _velocity;
}

void CharacterFireball::setPosition(Vector2 pos) {
    _pos = pos;
}

void CharacterFireball::hitBlockHorizontal() {
    _active = false;
    _velocity = {0.0f, 0.0f};
    m_animation.setFrames(EnemySprite::FireballSprite::CharacterFireballFrames);
    m_animation.resetCurrentFrame();
}

void CharacterFireball::hitBlockVertical(bool isMoveDown) {
    this->isMoveDown = isMoveDown;
    if(isMoveDown) {
        _velocity.y = _velocity_y;
    }
    else {
        _velocity.y = -_velocity_y;
    }
}