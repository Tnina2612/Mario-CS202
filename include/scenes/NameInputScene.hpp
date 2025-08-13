#pragma once
#include "core/Scene.hpp"
#include "core/InputField.hpp"
#include "raylib.h"
#include <string>

class TileMap;

class NameInputScene : public Scene {
private:
    RenderTexture2D renderTexture;
    TileMap* background;
    InputField* inputField;

public:
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    ~NameInputScene();
};