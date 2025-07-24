#pragma once

#include"raylib.h"

#include"IEnemyState.hpp"
#include"Enemy.hpp"

class Koopa;

class IKoopaState {
public:
    virtual ~IKoopaState() = default;
    virtual void enter(Koopa& koopa) = 0;
    virtual void update(Koopa& koopa, float dt) = 0;
    virtual void handleStomp(Koopa& koopa) = 0;
};


class Koopa : public Enemy {
private:
    std::unique_ptr<IKoopaState> m_state;
    int _recoveryTime;
    // enum KoopaState {

    // };
    //KoopaState m_state;
public:
    const int TIME = 3.f; //for recover in shell state
    Koopa();
    Koopa(const std::string& name);
    Koopa(const std::string& name, Vector2 pos);
    //Koopa(Vector2 bSpeed, Vector2 pos, Vector2 vel);
    //void init(std::shared_ptr<EnemyType> newType, Vector2 startPosition);

    void setRecoveryTime(int t);
    void setState(std::unique_ptr<IKoopaState> state);
    int getRecoveryTime();
    // bool onHit() override;
    // bool onStomp() override;
    // bool beHitByFireball() override;

    //void draw() override;
    void update(float dt) override;
};


//State
class WingedKoopa : public IKoopaState {
public:
    void enter(Koopa& koopa) override;
    void update(Koopa& koopa, float dt) override;
    void handleStomp(Koopa& koopa) override;
};

class NormalKoopa : public IKoopaState {
public:
    void enter(Koopa& koopa) override;
    void update(Koopa& koopa, float dt) override;
    void handleStomp(Koopa& koopa) override;
};

class ShellKoopa : public IKoopaState {
public:
    void enter(Koopa& koopa) override;
    void update(Koopa& koopa, float dt) override;
    void handleStomp(Koopa& koopa) override;
};