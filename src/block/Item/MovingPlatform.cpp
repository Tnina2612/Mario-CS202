#include<string>
#include<iostream>
#include<cmath>
#include"raylib.h"
#include"block/Item/MovingPlatform.h"

std::shared_ptr<MovingPlatformType> MovingPlatformFactory::s_platformTypes = nullptr;

MovingPlatformType::MovingPlatformType(const std::string& path) {
    _texture = LoadTexture(path.c_str());
}

MovingPlatformType::~MovingPlatformType() {
    UnloadTexture(_texture);
}

MovingPlatform::MovingPlatform() {
}

MovingPlatform::MovingPlatform(Vector2 startPos, Vector2 endPos) 
    : MovingPlatform()
{
    _startPos = startPos;
    _endPos = endPos;
    _pos = startPos;
    // targetPos = endPos;
    targetPos = startPos;
    _velocity = Vector2{0.f, 0.f};
}

void MovingPlatform::setVelocity(Vector2 vel) {
    bool vertical = vel.x == 0; 
    _velocity = vel;
    _curVelocity = _velocity;
    // _acceleration = vertical ? vel.y * vel.y / 40.f : vel.x * vel.x / 40.f;
}

void MovingPlatform::setActive(bool isActive) {
    _isActive = isActive;
}

void MovingPlatform::setAllFrames(std::vector<Rectangle> frames) {
    allFrames = frames;
}

void MovingPlatform::setAniFrames(std::vector<Rectangle> frames) {
    m_animation.setFrames(frames);
}

void MovingPlatform::setType(std::shared_ptr<MovingPlatformType> type) {
    _type = type;
    m_animation.setSprite(_type->_texture);
}

Rectangle MovingPlatform::getRect() const {
    return Rectangle{ _pos.x, _pos.y, allFrames[0].width, allFrames[0].height };
}

void MovingPlatform::move(float dt) {
    if (!_isActive) return;

    Vector2 dirStart = Vector2{_pos.x - _startPos.x, _pos.y - _startPos.y};
    Vector2 dirEnd = Vector2{_pos.x - _endPos.x, _pos.y - _endPos.y};

    Vector2 dirTar = Vector2{targetPos.x - _pos.x, targetPos.y - _pos.y};

    Vector2 dir; 
        dir.x = dirTar.x > 0 ? 1 : (dirTar.x < 0 ? -1 : 0); 
        dir.y = dirTar.y > 0 ? 1 : (dirTar.y < 0 ? -1 : 0);

    bool in = dirStart.x * dirEnd.x <= 0 && dirStart.y * dirEnd.y <= 0;

    if(!in) {
        _pos = targetPos;
        targetPos = (targetPos.x == _startPos.x && targetPos.y == _startPos.y) 
                    ? _endPos : _startPos;
        _curVelocity = Vector2{0.f, 0.f};
        return;
    }

    float disTarget = sqrt(pow(targetPos.x - _pos.x, 2) + pow(targetPos.y - _pos.y, 2));
    float distance = sqrt(pow(_startPos.x - _endPos.x, 2) + pow(_startPos.y - _endPos.y, 2));

    if(disTarget < pow(10, -3)) {
        _pos = targetPos;
        targetPos = (targetPos.x == _startPos.x && targetPos.y == _startPos.y) 
                    ? _endPos : _startPos;
        _curVelocity = Vector2{0.f, 0.f};
    }
    else if(disTarget < 20.f) {
        _curVelocity.x += -1*dir.x*_acceleration * dt;
        _curVelocity.y += -1*dir.y*_acceleration * dt;

        if(_curVelocity.x * dir.x <= 0) {
            _curVelocity.x = 24.f * dir.x;
        }
        if(_curVelocity.y * dir.y <= 0) {
            _curVelocity.y = 24.f * dir.y;
        }
    }
    else if(distance - disTarget < 20.f) {
        _curVelocity.x += dir.x * _acceleration  * dt;
        _curVelocity.y += dir.y * _acceleration * dt;

        if(_curVelocity.x * dir.x > _velocity.x) {
            _curVelocity.x = _velocity.x * dir.x;
        }
        if(_curVelocity.y * dir.y > _velocity.y) {
            _curVelocity.y = _velocity.y * dir.y;
        }
    }
    else {
        _curVelocity.x = _velocity.x * dir.x;
        _curVelocity.y = _velocity.y * dir.y;
    }

    _pos.x += _curVelocity.x * dt;
    _pos.y += _curVelocity.y * dt;
}

void MovingPlatform::draw() {
    if(!_isActive) {
        return;
    }
    m_animation.draw(_pos);
}

void MovingPlatform::update(float dt) {
    if (!_isActive) {
        return;
    }
    move(dt);
    m_animation.update(dt);
}


std::shared_ptr<MovingPlatform> MovingPlatformFactory::createPlatform(int type, Vector2 startPos, Vector2 endPos) {
    if(type < 0 || type > 5) {
        return nullptr;
    }

    auto platform = std::make_shared<MovingPlatform>(startPos, endPos);
    if (!s_platformTypes) {
        s_platformTypes = std::make_shared<MovingPlatformType>();
    }

    platform->setType(s_platformTypes);

    Vector2 velocity = Vector2{0.f, 0.f};
    std::vector<Rectangle> frames;

    if(type < 3) {
        velocity = Vector2{32.f, 0.f};
    }
    else {
        velocity = Vector2{0.f, 32.f};
    }

    if(type % 3 == 0) {
        frames.push_back(ItemSprite::PLATFORM_MOVING_3);
    }
    else if(type % 3 == 1) {
        frames.push_back(ItemSprite::PLATFORM_MOVING_4);
    }
    else {
        frames.push_back(ItemSprite::PLATFORM_MOVING_6);
    }

    platform->setVelocity(velocity);
    platform->setAllFrames(frames);
    platform->setAniFrames(frames);

    return platform;
}