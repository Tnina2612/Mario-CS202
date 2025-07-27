#pragma once
#include "core/Scene.hpp"

class TileMap;

class MapSelectScene : public Scene {
private:
    RenderTexture2D renderTexture;
    TileMap* background;
    Texture2D coin;
    Texture2D cursor;
    int cursorRow[8] = {150, 220, 290, 360, 430, 500, 570, 640};
    int cursorCol[4] = {120, 320, 520, 720};
    int curModeRow = 0;
    int curModeCol = 0;

public:
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    ~MapSelectScene();
};