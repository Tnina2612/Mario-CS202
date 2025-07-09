#pragma once
#include "core/Scene.hpp"
#include "raylib.h"

class Level;

class TitleScene : public Scene {
private:
    RenderTexture2D renderTexture;
    Level* background;
    Texture2D logo;
    Texture2D copyright;
    Texture2D cursor;
    int cursorPos[2] = {580, 640};
    int curMode = 0;

public:
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    void cleanup() override;
    ~TitleScene();
};