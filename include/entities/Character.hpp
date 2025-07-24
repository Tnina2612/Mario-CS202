#pragma once
#include "GameObject.hpp"
#include "raylib.h"
#include "../core/Variables.hpp"
#include <cstring>
#include"Animation.hpp"
#include <vector>
#include <iostream>
#include<algorithm>

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
    float accelerationX;
    float accelerationY;
    Orientation orientation;
    CharacterState characterState;
    const float gravity = 3900.0f;
    const float maxVeclocityX = 300.f;
    Behavior behavior;
    bool isInvincible;
    bool isDead;
    bool onGround;
    const float jumpVeclocity = 1550.0f; // Initial jump velocity
    const float brakeAcceleration = 600.0f; // Deceleration when braking
public:
    Character();
    Character(const vector<Rectangle>& frames, const Texture2D& sprite);
    void setState(IState* state);
    void moveLeft();
    void moveRight();
    void brakeLeft();
    void brakeRight();
    void jump();

    void setVelocityX(float velocity);
    void setVeclocityY(float velocity);
    float getJumpVelocity() const;

    void update();
    void draw();
    void setBehavior(Behavior newBehavior);
    Behavior getBehavior()const;
    void setOrientation(Orientation newOrientation);
    Orientation getOrientation() const;

    CharacterState getCharacterState() const;

    void hitBlockLeft();
    void hitBlockRight();
    void hitBlockTop();
    void hitBlockBottom();

    bool getOnGround() const;
    void setOnGround(bool onGround);
    
    // void takeDamage();
    // void onCollision(GameObject* obj);
    // void addScore(int points);


    Rectangle getRectangle() const;
    virtual ~Character();
    virtual CharacterType getType() const = 0; // Pure virtual function to get character type

    Vector2 getPos() const;
};