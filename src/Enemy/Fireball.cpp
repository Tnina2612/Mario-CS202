#include<cmath>
#include<iostream>

#include"../../include/entities/Enemy/Fireball.hpp"
#include"../../include/entities/Enemy/EnemyFactory.hpp"

Fireball::Fireball() {
    allFrames = EnemySprite::Fireball::Frames;
    m_animation.sprite = EnemyFactory::getEnemyTypes()->sprite;
    
}

Fireball::Fireball(Vector2 startPos, Vector2 targetPos) : Fireball() {
    _width = 25.f;
    _height = 25.f;
    _pos = startPos;
    _targetPos = targetPos;
    _spawing = true;
    _dir = targetPos.x - startPos.x > 0 ? 1 : -1;

    Vector2 temp = Vector2{targetPos.x - startPos.x, targetPos.y - startPos.y};
    float d = sqrt(temp.x*temp.x + temp.y*temp.y);

    if (d != 0.0f) {
        
        temp = Vector2{temp.x / d, temp.y / d};
        _velocity = Vector2{100.f * temp.x * _dir, 100.f * temp.y};
        
        if (_dir == 1)
            m_animation.setFrames(allFrames["Right"]);
        else
            m_animation.setFrames(allFrames["Left"]);
    } 
    else {
        _velocity = Vector2{0.f, 0.f};
        _dir =0.f;
        m_animation.setFrames(allFrames["Left"]);
    }
}

Rectangle Fireball::getHitBox() {
    return Rectangle{_pos.x, _pos.y, _width, _height};
}

void Fireball::update(float dt) {
    _pos.x += _velocity.x * dt;
    _pos.y += _velocity.y * dt;

    m_animation.update(dt);
    if(_spawing) {
        if(pow(_pos.x-_targetPos.x, 2)+ pow(_pos.y-_targetPos.y, 2 ) < 120.f) {
            _spawing = false;
            //_pos = _targetPos;
            _velocity = Vector2{50.f * _dir, 0};
        }
    }
}

void Fireball::draw() {
    m_animation.draw(_pos);
}