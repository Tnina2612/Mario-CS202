#include "ui/HUD.hpp"
#include "core/Program.h"
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
        case EventType::RESET_TIMER:
            session->TIMELEFT = 400;
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

    DrawTextEx(font, "MARIO", { 60, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "COINS", { 290, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "WORLD", { 498, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "TIME",  { 702, 14 }, 24, 1, WHITE);
    DrawTextEx(font, "LIVES", { 878, 14 }, 24, 1, WHITE);

    DrawTextEx(font, scoreText, { 60, 35 }, 24, 1, WHITE);
    DrawTextureEx(coin, {290, 39}, 0.0f, 2.8f, WHITE);
    DrawText("x", 310, 40, 20, WHITE);
    DrawTextEx(font, coinText.c_str(), { 330, 35 }, 24, 1, WHITE);
    DrawTextEx(font, worldText.c_str(), { 498, 35 }, 24, 1, WHITE);
    DrawTextEx(font, timeText.c_str(),  { 702, 35 }, 24, 1, WHITE);
    DrawTextEx(font, livesText.c_str(), { 878, 35 }, 24, 1, WHITE);
}