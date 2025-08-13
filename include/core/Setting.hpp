#pragma once
#include "core/Scene.hpp"
#include "core/GameSession.hpp"
#include "ui/HUD.hpp"
#include "level/Level.hpp"
#include "raylib.h"

class Setting {
private:
    Texture2D icon;
    Texture2D iconHovered;
    float x;
    float y;
    bool isOn;
    Level* level;

    Setting();

public:
    Setting(const Setting&) = delete;
    void operator=(const Setting&) = delete;

    static Setting& getInstance(); 
    ~Setting();

    void draw();
    void handleInput(Level* level);
    bool isHovered();
    bool isClicked();
    void onClick(Level* level);
};