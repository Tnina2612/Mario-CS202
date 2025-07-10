#pragma once
#include "GameObject.hpp"
#include "raylib.h"
#include "../Variables.h"
#include <cstring>

class GameObject;

class IState {
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void enter() = 0;
};

class Character {
private:
    Vector2 pos;
    IState* state;
    Texture2D sprite;
    float invincibilityTime; // Time in seconds
    int lives; // Number of lives
    int score;
    float veclocityX;
    float veclocityY;
public:
    Character();
    Character(const string& spritePath);
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
};