#pragma once
#include "ui/IObserver.hpp"
#include "core/GameSession.hpp"
#include "raylib.h"
#include <utility>

class EventManager;

// Concrete Observer in Observer Pattern
class HUD : public IObserver {
private:
    GameSession* session;
    Texture2D coin;
    float timeAccumulator = 0.0f;

public:
    HUD(GameSession* s);
    ~HUD();
    void onNotify(EventType type) override;
    void update(float deltaTime);
    void draw();
};