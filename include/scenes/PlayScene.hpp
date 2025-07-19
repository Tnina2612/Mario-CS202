#pragma once
#include "core/Scene.hpp"
#include "ui/EventManager.hpp"
#include <memory>

class Character;
class Level;

class PlayScene : public Scene {
private:
    Level* level;
    EventManager eventManager;
    Camera2D camera;
    RenderTexture2D renderTexture;
    std::shared_ptr<Character> character;

public:
    ~PlayScene();

    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;

    void setUpCamera();
};