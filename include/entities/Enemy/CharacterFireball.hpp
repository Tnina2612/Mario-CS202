#pragma once

#include<vector>
#include"raylib.h"

#include<entities/Animation.hpp>
#include<entities/Effect.hpp>

class CharacterFireball {
private:
    float _width;               //< for hitbox
    float _height;              //< for hitbox
    Orientation orientation;
    //Vector2 _startPos;
    Vector2 _pos;
    Vector2 _velocity;
    Animation m_animation;
    const float _velocity_y = 100.0f;
    const float gravity = 1000.0f; // Gravity effect on the fireball
    Effect bombEffect;

    std::unordered_map<std::string, std::vector<Rectangle>> allFrames;
    bool isMoveDown = true;
    bool _onScreen;
    bool _active;
public:
    CharacterFireball();
    CharacterFireball(Vector2 startPos, Orientation orienntation);
    
    Rectangle getHitBox();
    bool isOffScreen();
    bool getActive()const;

    
    
    void update(float dt = GetFrameTime());
    void draw();
    bool getOnScreen()const;
    Vector2 getVelocity()const;
    void setPosition(Vector2 pos);
    void hitBlockVertical(bool isMoveDown);
    void hitBlockHorizontal();

};