#pragma once
#include "core/Scene.hpp"

class DeathScene : public Scene {
private:
    Texture2D marioIcon;
    float waitTimer;
    float waitDuration;
    bool hasTriggeredTransition;
    
public:
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    void cleanup() override;
    ~DeathScene();
};