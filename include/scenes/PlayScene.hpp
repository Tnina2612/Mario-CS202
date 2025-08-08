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

public:
    PlayScene(const std::string& levelName);
    PlayScene(std::string subLevelFolder, Vector2 playerPosition, int numLives = 3);
    ~PlayScene();

    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
};