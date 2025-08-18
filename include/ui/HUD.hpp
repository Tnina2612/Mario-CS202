#pragma once
#include "ui/IObserver.hpp"
#include "core/GameSession.hpp"
#include "raylib.h"
#include <utility>
#include <vector>
#include <string>
#include <queue>
#include <tuple>

class EventManager;

// Concrete Observer in Observer Pattern
class HUD : public IObserver {
private:
    GameSession* session;
    Texture2D coin;
    float timeAccumulator = 0.0f;

    std::vector<std::string> levelAnnouncement;
    std::vector<std::tuple<std::string, Vector2, float>> inGameNotification;
public:
    HUD(GameSession* s);
    ~HUD();
    void onNotify(EventType type) override;
    void onNotify(EventType type, Vector2 pos);
    void update(float deltaTime);
    void draw();
    void addLevelAnnouncement(std::string line);
    void clearLevelAnnouncement();
};