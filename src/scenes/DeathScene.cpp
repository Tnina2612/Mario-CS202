#include "core/Variables.hpp"
#include "../../assets/images/Coordinate.h"
#include "scenes/DeathScene.hpp"
#include "scenes/PlayScene.hpp"
#include "core/MusicManager.hpp"
#include "raylib.h"

DeathScene::DeathScene() {
    // Store current session state
    finalSession = Program::getInstance().getSession();
    MusicManager::getInstance().stopMusic();
}

void DeathScene::init() {
    marioIcon = LoadTexture("assets/images/sprite-sheets/mario.png");

    waitTimer = 0.0f;
    waitDuration = 3.0f;
}

void DeathScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        Program::getInstance().changeScene(new PlayScene("1-1"));
    }
}

void DeathScene::update() {
    waitTimer += GetFrameTime();
    
    // Automatically transition after 3 seconds
    if (waitTimer >= waitDuration) {
        Program::getInstance().changeScene(new PlayScene("1-1"));
    }
}

void DeathScene::render() {
    ClearBackground(BLACK);

    // Draw game session
    Font font = Program::getInstance().getFont();
    GameSession session = Program::getInstance().getSession();

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

    std::string worldText_ = "WORLD " + std::to_string(session.WORLD.first) + "-" + std::to_string(session.WORLD.second);
    Vector2 textSize = MeasureTextEx(Program::getInstance().getFont(), worldText_.c_str(), 32, 1);
    float x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    float y = (Global::WINDOW_HEIGHT - textSize.y) / 2.0f - 15.0f;
    DrawTextEx(Program::getInstance().getFont(), worldText_.c_str(), {x, y - 50.0f}, 32, 1, WHITE);

    DrawTexturePro(marioIcon, CharacterSprite::Small::Right::Idle, {400, 500, 55, 64}, {0, 0}, 0.0f, WHITE);

    std::string livesText_ = "  x  " + std::to_string(session.LIVES);
    textSize = MeasureTextEx(Program::getInstance().getFont(), livesText_.c_str(), 32, 1);
    x = (Global::WINDOW_WIDTH - textSize.x) / 2.0f;
    DrawTextEx(Program::getInstance().getFont(), livesText_.c_str(), {x + 20.0f, y + 85.0f}, 32, 1, WHITE);
}

DeathScene::~DeathScene() {
    UnloadTexture(marioIcon);
    UnloadTexture(coin);
}