#pragma once
#include "core/Scene.hpp"
#include <core/Program.hpp>

class DeathScene : public Scene {
private:
    Texture2D marioIcon;
    Texture2D coin;
    GameSession finalSession;
    float waitTimer;
    float waitDuration;
    
public:
    DeathScene();
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    ~DeathScene();
};