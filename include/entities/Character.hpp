#pragma once
#include "GameObject.hpp"

class GameObject;

class IState {
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void enter() = 0;
};

class Character {
private:
    IState* state;
    float invincibilityTime; // Time in seconds
    int lives; // Number of lives
    int score;
    float veclocityX;
    float veclocityY;
public:
    Character();
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