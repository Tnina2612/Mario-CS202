#pragma once
#include "core/Scene.hpp"
#include <vector>
#include <string>

class TileMap;

class LoadGameScene : public Scene {
private:
    RenderTexture2D renderTexture;
    TileMap* background;
    Texture2D coin;
    Texture2D cursor;
    float initialPos = 170;
    int curRow = 0;

    std::vector<std::pair<std::string, std::string>> playerList;

public:
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    ~LoadGameScene();
};