#pragma once

class Enemy;

class IEnemyState {
public:
    virtual ~IEnemyState() = default;
    virtual void enter(Enemy& enemy) = 0;
    virtual void update(Enemy& enemy, float dt) = 0;
};