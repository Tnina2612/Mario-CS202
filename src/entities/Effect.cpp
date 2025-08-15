#include<entities/Effect.hpp>
#include<iostream>

void Effect::handleEffect(float deltaTime) {
    if(*inEffect == false) {
        counterTime = effectTime;
        return;
    }
    if(counterTime <= 0.0f) {
        counterTime = effectTime;
        *inEffect = false;
        return;
    }
    counterTime -= deltaTime;
}

void Effect::addEffect(float effectTime, bool* inEffect) {
    this->effectTime = effectTime;
    this->inEffect = inEffect;
    *inEffect = true;
    counterTime = effectTime;
}