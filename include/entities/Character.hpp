#pragma once
#include "GameObject.hpp"
#include "raylib.h"
#include "../core/Variables.hpp"
#include <cstring>
#include"Animation.hpp"
#include <vector>
#include <iostream>
#include<algorithm>
#include<entities/Effect.hpp>
#include<entities/Enemy/CharacterFireball.hpp>

class GameObject;


class IState {
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void enter() = 0;
};

class Character; 

class PlayerLevelAnimationManager {
private:
    Character* character;
public:
    PlayerLevelAnimationManager(Character* character);
    void goDownward();
    void goUpward();
    void goLeftward();
    void goRightward();
    void climbDown(float pivotX);
    void disappear();
    void appear();
};

// Now define Character, which can use IntoPipeAnimation
class Character {
protected:
    Vector2 pos;
    IState* state;
    float invincibilityTime; // Time in seconds
    int score;
    float veclocityX;
    float veclocityY;
    float accelerationX;
    float accelerationY;
    Orientation orientation;
    CharacterState characterState;
    const float gravity = 1000; //3900.0f;
    const float maxVeclocityX = 90; //300.f;
    Behavior behavior;
    bool isInvincible;
    bool isDead;
    bool onGround;
    bool collideLeft;
    bool collideRight;
    bool collideDown;
    const float jumpVeclocity = 380; //1550.0f; // Initial jump velocity
    const float brakeAcceleration = 200; //600.0f; // Deceleration when braking
    const float restVeclocity = 50.0f;
    float timeEffect;
    bool onAnimation;
    bool isInvicinbleBlinking = false;
    
    bool isDebug = false;
    bool growthUp;
    bool shrinkDown;
    bool isThrow;
    bool isStarMan;
    Animation mAnimation;
    vector<Effect*> effects;
    vector<CharacterFireball*> fireballs;

public:
    PlayerLevelAnimationManager playerLevelAnimationManager;

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
    void debug();
    void setBehavior(Behavior newBehavior);
    void powerUp();
    Behavior getBehavior()const;
    void setOrientation(Orientation newOrientation);
    Orientation getOrientation() const;

    CharacterState getCharacterState() const;
    Animation& getAnimation();

    void hitBlockLeft(float vline = 0.0);
    void hitBlockRight(float vline = 0.0);
    void hitBlockTop(float hline = 0.0);
    void hitBlockBottom(float hline = 0.0);
    void createFireball();
    bool getOnGround() const;
    void setOnGround(bool onGround);
    bool getCollideRight()const;
    bool getCollideLeft()const;
    float getVeclocityX()const;
    float getVeclocityY()const;
    void setPosition(float x, float y);
    float getGravity()const;
    float getRestVeclocity()const;
    void handleEffect(float deltaTime = GetFrameTime());
    void handleFireballEffect(float deltaTime = GetFrameTime());
    vector<CharacterFireball*>& getFireballs();
    void takeDamage();
    // bool getCollideUp()const;
    // bool getCollideDown()const;
    
    // void takeDamage();
    // void onCollision(GameObject* obj);
    // void addScore(int points);


    Rectangle getRectangle() const;
    virtual ~Character();
    virtual CharacterType getType() const = 0; // Pure virtual function to get character type


    Vector2 getPos() const;
    bool getIsDead() const;
};