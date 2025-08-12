#pragma once

#include"raylib.h"

#include"Enemy.hpp"

class Koopa;

class IKoopaState {
public:
    virtual ~IKoopaState() = default;
    virtual void enter(Koopa& koopa) = 0;
    virtual void update(Koopa& koopa, float dt) = 0;
    virtual void handleStomp(Koopa& koopa) = 0;
    virtual void onEnemyCollision(Koopa& koopa, Enemy& other) = 0;
    virtual void hitBlock(Koopa& koopa) = 0;
};


class Koopa : public Enemy {
private:
    std::unique_ptr<IKoopaState> m_state;
    float _recoveryTime;
    int _deadAni = 0;   //0: normal, 1: dead, -1: offscreen
    bool _inShell = false;

    // void deadState();
public:
    const float TIME = 7.f; //for recover in shell state
    Koopa();
    Koopa(const std::string& name);
    Koopa(const std::string& name, Vector2 pos);

    void setRecoveryTime(float t);
    void setState(std::unique_ptr<IKoopaState> state);
    float getRecoveryTime();

    //bool onHit() override;
    void hitBlockLeft() override;
    void hitBlockRight() override;

    void hitVertical(int dir) override;
    void changeDirection() override;
    bool onStomp() override;
    bool setInShell(bool inShell);
    //bool beHitByFireball() override;
    bool physics() override;

    void onEnemyCollision(Enemy& enemy) override;
    void update(float dt) override;
};


//State
class WingedKoopa : public IKoopaState {
public:
    void enter(Koopa& koopa) override;
    void update(Koopa& koopa, float dt) override;
    void handleStomp(Koopa& koopa) override;
    void onEnemyCollision(Koopa& koopa, Enemy& other) override;
    void hitBlock(Koopa& koopa) override;
};

class NormalKoopa : public IKoopaState {
public:
    void enter(Koopa& koopa) override;
    void update(Koopa& koopa, float dt) override;
    void handleStomp(Koopa& koopa) override;
    void onEnemyCollision(Koopa& koopa, Enemy& other) override;
    void hitBlock(Koopa& koopa) override;
};

class ShellKoopa : public IKoopaState {
public:
    void enter(Koopa& koopa) override;
    void update(Koopa& koopa, float dt) override;
    void handleStomp(Koopa& koopa) override;
    void onEnemyCollision(Koopa& koopa, Enemy& other) override;
    void hitBlock(Koopa& koopa) override;
};