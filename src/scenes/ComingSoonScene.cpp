#include "core/Program.hpp"
#include "scenes/ComingSoonScene.hpp"
#include "level/TileMap.hpp"
#include "raylib.h"

void ComingSoonScene::init() {
    background = new TileMap("world-maps/titleScene/titleScene.txt");
    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);

    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        background->draw();
    EndTextureMode();
}

void ComingSoonScene::handleInput() {

}

void ComingSoonScene::update() {

}

void ComingSoonScene::render() {
   DrawTexturePro(renderTexture.texture, 
            Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT},
            Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT},
            Vector2{0, 0}, 0, WHITE);

    Font font = Program::getInstance().getFont();

    Vector2 textSize = MeasureTextEx(Program::getInstance().getFont(), "COMING SOON...", 40, 1);
    float x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    float y = (Global::WINDOW_HEIGHT - textSize.y) / 2.0f;
    
    DrawTextEx(Program::getInstance().getFont(), "COMING SOON...", {x, y}, 40, 1, WHITE);
}