#pragma once
#include "core/Scene.hpp"

class TileMap;

class ComingSoonScene : public Scene {
private:
    RenderTexture2D renderTexture;
    TileMap* background;

public:
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    ~ComingSoonScene() = default;
};