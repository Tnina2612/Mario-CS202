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

class Character; 

class LevelPlayerAnimationManager {
private:
    Character* character;
public:
    LevelPlayerAnimationManager(Character* character);
    void goDownward();
    void goUpward();
    void goLeftward();
    void goRightward();
    void climbDown(float pivotX);
    void disappear();
    void appear();
};

// Now define Character, which can use IntoPipeAnimation
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
    const float gravity = 1300; //3900.0f;
    const float maxVeclocityX = 100; //300.f;
    Behavior behavior;
    bool isInvincible;
    bool isDead;
    bool onGround;
    bool collideLeft;
    bool collideRight;
    bool collideDown;
    const float jumpVeclocity = 500; //1550.0f; // Initial jump velocity
    const float brakeAcceleration = 200; //600.0f; // Deceleration when braking
    const float restVeclocity = 50.0f;
    float timeEffect;
    
public:
    LevelPlayerAnimationManager levelPlayerAnimationManager;

    Character();
    Character(const vector<Rectangle>& frames, const Texture2D& sprite);
    void setState(IState* state);
    void moveLeft();
    void moveRight();
    void brakeLeft();
    void brakeRight();
    void jump();
    void die();
    void setVelocityX(float velocity);
    void setVeclocityY(float velocity);
    float getJumpVelocity() const;

    void resetAttributes();
    void update();
    void draw();
    void setBehavior(Behavior newBehavior);
    Behavior getBehavior()const;
    void setOrientation(Orientation newOrientation);
    Orientation getOrientation() const;

    CharacterState getCharacterState() const;

    void hitBlockLeft(float vline = 0.0);
    void hitBlockRight(float vline = 0.0);
    void hitBlockTop(float hline = 0.0);
    void hitBlockBottom(float hline = 0.0);
    void climb(float TimeEffect = -1);
    void Growth(float TimeEffect = -1);
    bool getOnGround() const;
    void setOnGround(bool onGround);
    bool getCollideRight()const;
    bool getCollideLeft()const;
    float getVeclocityX()const;
    float getVeclocityY()const;
    void setPosition(float x, float y);
    float getGravity()const;
    float getRestVeclocity()const;
    // bool getCollideUp()const;
    // bool getCollideDown()const;
    
    // void takeDamage();
    // void onCollision(GameObject* obj);
    // void addScore(int points);


    Rectangle getRectangle() const;
    virtual ~Character();
    virtual CharacterType getType() const = 0; // Pure virtual function to get character type


    Vector2 getPos() const;
};