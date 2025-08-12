#include "ui/HUD.hpp"
#include "core/Program.hpp"
#include <string>
#include <cstdio>

HUD::HUD(GameSession* s) {
    session = s;
    coin = LoadTexture("assets/images/title-scene/coin.png");
}

HUD::~HUD() {
    UnloadTexture(coin);
}

void HUD::onNotify(EventType type) {
    switch (type) {
        case EventType::ADDSCORE:
            session->SCORE += 100;
            break;
        case EventType::COLLECT_COINS:
            session->COINS++;
        case EventType::ADDLIVES:
            session->LIVES++;
            break;
        case EventType::MARIO_DIED:
            session->LIVES--;
            break;
        case EventType::RESET_TIMER:
            session->TIMELEFT = 400;
            break;
        case EventType::RESET_LIVES:
            session->LIVES = 3;
            break;
        case EventType::RESET_SCORES:
            session->SCORE = 0;
            break;
        default:
            break;
    }
}

void HUD::update(float deltaTime) {
    timeAccumulator += deltaTime;
    
    // Decrease timer every second
    if (timeAccumulator >= 0.5f) {
        session->TIMELEFT--;
        timeAccumulator -= 0.5f;
    }
    
    if (session->TIMELEFT < 0) session->TIMELEFT = 0;
}

void HUD::draw() {
    Font font = Program::getInstance().getFont();

    char scoreText[7];
    snprintf(scoreText, sizeof(scoreText), "%06d", session->SCORE);
    std::string coinText = std::to_string(session->COINS);
    std::string worldText = std::to_string(session->WORLD.first) + "-" + std::to_string(session->WORLD.second);
    std::string timeText  = std::to_string(session->TIMELEFT);
    std::string livesText = std::to_string(session->LIVES);

    DrawTextEx(font, "MARIO", { 20, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "COINS", { 240, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "WORLD", { 438, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "TIME",  { 632, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "LIVES", { 798, 14 }, 24, 1, WHITE);

    DrawTextEx(font, scoreText, { 20, 35 }, 24, 1, WHITE);
    DrawTextureEx(coin, {240, 39}, 0.0f, 2.8f, WHITE);
    DrawText("x", 260, 40, 20, WHITE);
    DrawTextEx(font, coinText.c_str(), { 280, 35 }, 24, 1, WHITE);
    DrawTextEx(font, worldText.c_str(), { 460, 35 }, 24, 1, WHITE);
    DrawTextEx(font, timeText.c_str(),  { 655, 35 }, 24, 1, WHITE);
    DrawTextEx(font, livesText.c_str(), { 798, 35 }, 24, 1, WHITE);
}