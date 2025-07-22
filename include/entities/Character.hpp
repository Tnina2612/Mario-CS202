#pragma once
#include "GameObject.hpp"
#include "raylib.h"
#include "../Variables.h"
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

class Character : public Animation, public InputManager::Listener {
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
    const float gravity = 1300.0f;
    const float maxVeclocityX = 100.f;
    Behavior behavior;
    bool isInvincible;
    bool isDead;
    bool onGround;
    const float jumpVeclocity = 400.0f; // Initial jump velocity
    const float brakeAcceleration = 200.0f; // Deceleration when braking
    InputManager& inputManager;
    
public:
    Character();
    Character(const vector<Rectangle>& frames, const Texture2D& sprite);
    void setState(IState* state);
    void moveLeft();
    void moveRight();
    void brakeLeft();
    void brakeRight();
    void jump();

    void baseInputUpdate();
    void update();
    void draw();
    void takeDamage();
    void onCollision(GameObject* obj);
    void addScore(int points);

    virtual ~Character();
    virtual CharacterType getType() const = 0; // Pure virtual function to get character type
    void onkey(KeyboardKey key, bool active)override;
};