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
    float waitTimer;
    float waitDuration;
    string sessionName;
    
public:
    static bool is2players;
    static bool isMario;
    PlayScene(const std::string& levelName);
    PlayScene(std::string subLevelFolder, Vector2 playerPosition);
    ~PlayScene();

    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;

    string getSessionName() const {
        return sessionName;
    }
};