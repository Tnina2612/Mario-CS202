#pragma once

#include<vector>
#include"raylib.h"

#include<entities/Animation.hpp>

class CharacterFireball {
private:
    float _width;               //< for hitbox
    float _height;              //< for hitbox
    int _dir;
    //Vector2 _startPos;
    Vector2 _pos;
    Vector2 _velocity;
    Animation m_animation;

    std::unordered_map<std::string, std::vector<Rectangle>> allFrames;
    bool _spawing;
public:
    CharacterFireball();
    CharacterFireball(Vector2 startPos, Vector2 targetPos);
    
    Rectangle getHitBox();
    bool isOffScreen();
    
    void update(float dt = GetFrameTime());
    void draw();
};