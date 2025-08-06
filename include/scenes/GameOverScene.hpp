#pragma once
#include "core/Scene.hpp"
#include "core/GameSession.hpp"

class GameOverScene : public Scene {
private:
    float waitTimer;
    float waitDuration;
    GameSession finalSession;
    Texture2D coin;

public:
    GameOverScene();
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    ~GameOverScene();
};