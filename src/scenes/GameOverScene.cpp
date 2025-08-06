#include "core/Program.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/TitleScene.hpp"
#include "core/SoundManager.hpp"
#include "raylib.h"
#include <string>
#include <cstdio>

GameOverScene::GameOverScene() {
    // Store current session state
    finalSession = Program::getInstance().getSession();
    SoundManager::getInstance().playSound(SoundType::GAMEOVER);
}

void GameOverScene::init() {
    // Initialize timer variables
    waitTimer = 0.0f;
    waitDuration = 3.0f;

    coin = LoadTexture("assets/images/title-scene/coin.png");
}

void GameOverScene::handleInput() {
    // Allow manual skip with ENTER key
    if (IsKeyPressed(KEY_ENTER)) {
        Program::getInstance().changeScene(new TitleScene());
    }
}

void GameOverScene::update() {
    waitTimer += GetFrameTime();
    
    // Automatically transition after 3 seconds
    if (waitTimer >= waitDuration) {
        Program::getInstance().changeScene(new TitleScene());
    }
}

void GameOverScene::render() {
    ClearBackground(BLACK);

    // Draw game session
    Font font = Program::getInstance().getFont();

    char scoreText[7];
    snprintf(scoreText, sizeof(scoreText), "%06d", finalSession.SCORE);
    std::string coinText = std::to_string(finalSession.COINS);
    std::string worldText = std::to_string(finalSession.WORLD.first) + "-" + std::to_string(finalSession.WORLD.second);
    std::string timeText  = std::to_string(finalSession.TIMELEFT);
    std::string livesText = std::to_string(finalSession.LIVES);

    DrawTextEx(font, "MARIO", { 60, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "COINS", { 290, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "WORLD", { 498, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "TIME",  { 702, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "LIVES", { 878, 14 }, 24, 1, WHITE);

    DrawTextEx(font, scoreText, { 60, 35 }, 24, 1, WHITE);
    DrawTextureEx(coin, {290, 39}, 0.0f, 2.8f, WHITE);
    DrawText("x", 310, 40, 20, WHITE);
    DrawTextEx(font, coinText.c_str(), { 330, 35 }, 24, 1, WHITE);
    DrawTextEx(font, worldText.c_str(), { 520, 35 }, 24, 1, WHITE);
    DrawTextEx(font, timeText.c_str(),  { 725, 35 }, 24, 1, WHITE);
    DrawTextEx(font, livesText.c_str(), { 965, 35 }, 24, 1, WHITE);
    
    Vector2 textSize = MeasureTextEx(Program::getInstance().getFont(), "GAME OVER", 40, 1);
    float x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    float y = (Global::WINDOW_HEIGHT - textSize.y) / 2.0f;
    
    DrawTextEx(Program::getInstance().getFont(), "GAME OVER", {x, y}, 40, 1, WHITE);
}

GameOverScene::~GameOverScene() {
    UnloadTexture(coin);
}