#pragma once
#include<raylib.h>
using namespace std;
class Effect {
protected:
    bool* inEffect;
    float effectTime;
    float counterTime;
public:
    Effect() : effectTime(0.0f), counterTime(0.0f) {}
    Effect(float effectTime, bool* inEffect) : effectTime(effectTime), counterTime(effectTime), inEffect(inEffect) {}
    virtual void handleEffect(float deltaTime = GetFrameTime());
    void addEffect(float effectTime, bool* inEffect);
    virtual ~Effect() {}
    float getCounterTime() const {
        return counterTime;
    }
};

class ChangeStateEffect : public Effect {
public:
    ChangeStateEffect() {}
    ChangeStateEffect(float effectTime, bool* inEffect) : Effect(effectTime, inEffect) {}
};

class ThrowEffect : public Effect {
public:
    ThrowEffect() {}
    ThrowEffect(float effectTime, bool* inEffect) : Effect(effectTime, inEffect) {}
};

class StarManEffect : public Effect {
public:
    StarManEffect() {}
    StarManEffect(float effecTime, bool* inEffect) : Effect(effecTime, inEffect) {}
};