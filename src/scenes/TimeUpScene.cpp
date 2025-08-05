#include "core/Variables.hpp"
#include "core/Program.hpp"
#include "scenes/TimeupScene.hpp"
#include "scenes/PlayScene.hpp"
#include "core/MusicManager.hpp"
#include "raylib.h"

void TimeupScene::init() {
    MusicManager::getInstance().stopMusic();

    waitTimer = 0.0f;
    waitDuration = 3.0f;
}

void TimeupScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        Program::getInstance().changeScene(new PlayScene());
    }
}

void TimeupScene::update() {
    waitTimer += GetFrameTime();
    
    // Automatically transition after 3 seconds
    if (waitTimer >= waitDuration) {
        Program::getInstance().changeScene(new PlayScene());
    }
}

void TimeupScene::render() {
    ClearBackground(BLACK);

    // Draw game session
    Program::getInstance().getHUD().draw();

    Vector2 textSize = MeasureTextEx(Program::getInstance().getFont(), "TIME UP", 40, 1);
    float x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    float y = (Global::WINDOW_HEIGHT - textSize.y) / 2.0f;
    
    DrawTextEx(Program::getInstance().getFont(), "TIME UP", {x, y}, 40, 1, WHITE);
}


TimeupScene::~TimeupScene() {
    
}