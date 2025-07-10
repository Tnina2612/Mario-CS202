#include "Variables.h"
#include "core/Program.h"
#include "scenes/DeathScene.hpp"
#include "scenes/PlayScene.hpp"
#include "raylib.h"

void DeathScene::init() {

}

void DeathScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        // Program::getInstance().changeScene(new PlayScene());
    }
}

void DeathScene::update() {

}

void DeathScene::render() {
    ClearBackground(BLACK);

    // Draw game session
    Program::getInstance().getHUD().draw();
    GameSession session = Program::getInstance().getSession();

    std::string worldText = "WORLD " + std::to_string(session.WORLD.first) + "-" + std::to_string(session.WORLD.second);
    Vector2 textSize = MeasureTextEx(Program::getInstance().getFont(), worldText.c_str(), 30, 1);
    float x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    float y = (Global::WINDOW_HEIGHT - textSize.y) / 2.0f - 15.0f;
    DrawTextEx(Program::getInstance().getFont(), worldText.c_str(), {x, y}, 30, 1, WHITE);

    std::string livesText = "  x  " + std::to_string(session.LIVES);
    textSize = MeasureTextEx(Program::getInstance().getFont(), livesText.c_str(), 30, 1);
    x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(Program::getInstance().getFont(), livesText.c_str(), {x, y + 30.0f}, 30, 1, WHITE);

    Program::getInstance().getHUD().draw();
}

void DeathScene::cleanup() {

}

DeathScene::~DeathScene() {
    cleanup();
}