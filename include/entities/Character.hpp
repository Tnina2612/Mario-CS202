#pragma once
#include "GameObject.hpp"
#include "raylib.h"
#include "../core/Variables.hpp"
#include <cstring>
#include"Animation.hpp"
#include <vector>

class GameObject;

class IState {
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void enter() = 0;
};

class Character : public Animation {
private:
    Vector2 pos;
    IState* state;
    float invincibilityTime; // Time in seconds
    int lives; // Number of lives
    int score;
    float veclocityX;
    float veclocityY;
    Orientation orientation;
    CharacterState characterState;
    const float friction = 100.0;
    const float gravity = 200.0f;
    const float maxVeclocityX = 100.f;
    enum Behavior {
        MOVE,
        JUMP,
        BRAKE,
        DUCK,
        THROW,
        IDLE
    };
    Behavior behavior;
    bool isInvincible;
    bool isDead;
    
public:
    Character();
    Character(const vector<Rectangle>& frames, const Texture2D& sprite);
    void setState(IState* state);
    void moveLeft();
    void moveRight();
    void jump();
    void update();
    void draw();
    void takeDamage();
    void onCollision(GameObject* obj);
    void addScore(int points);
    virtual ~Character();
    virtual CharacterType getType() const = 0; // Pure virtual function to get character type

    Vector2 getPos() const;
};