#include "core/Variables.hpp"
#include "../../assets/images/Coordinate.h"
#include "core/Program.hpp"
#include "scenes/DeathScene.hpp"
#include "scenes/PlayScene.hpp"
#include "raylib.h"

void DeathScene::init() {
    marioIcon = LoadTexture("assets/sprites sheets/mario.png");

    waitTimer = 0.0f;
    waitDuration = 3.0f;
    hasTriggeredTransition = false;
}

void DeathScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)  && !hasTriggeredTransition) {
        // Program::getInstance().changeScene(new PlayScene());
    }
}

void DeathScene::update() {
    if (!hasTriggeredTransition) {
        waitTimer += GetFrameTime();
        
        // Automatically transition after 3 seconds
        if (waitTimer >= waitDuration) {
            hasTriggeredTransition = true;
            // Program::getInstance().changeScene(new PlayScene());
        }
    }
}

void DeathScene::render() {
    ClearBackground(BLACK);

    // Draw game session
    Program::getInstance().getHUD().draw();
    GameSession session = Program::getInstance().getSession();

    std::string worldText = "WORLD " + std::to_string(session.WORLD.first) + "-" + std::to_string(session.WORLD.second);
    Vector2 textSize = MeasureTextEx(Program::getInstance().getFont(), worldText.c_str(), 32, 1);
    float x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    float y = (Global::WINDOW_HEIGHT - textSize.y) / 2.0f - 15.0f;
    DrawTextEx(Program::getInstance().getFont(), worldText.c_str(), {x, y - 50.0f}, 32, 1, WHITE);

    DrawTexturePro(marioIcon, CharacterSprite::Small::Right::Idle, {400, 500, 55, 64}, {0, 0}, 0.0f, WHITE);

    std::string livesText = "  x  " + std::to_string(session.LIVES);
    textSize = MeasureTextEx(Program::getInstance().getFont(), livesText.c_str(), 32, 1);
    x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(Program::getInstance().getFont(), livesText.c_str(), {x + 20.0f, y + 85.0f}, 32, 1, WHITE);

    Program::getInstance().getHUD().draw();
}

DeathScene::~DeathScene() {
    UnloadTexture(marioIcon);
}