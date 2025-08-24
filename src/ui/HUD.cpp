#include "ui/HUD.hpp"
#include "core/Program.hpp"
#include <string>
#include <cstdio>
#include <scenes/PlayScene.hpp>

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
            session->TIMELEFT = 800;
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

void HUD::onNotify(EventType type, Vector2 pos) {
    const float existingTime = 0.5f;

    switch (type) {
        case EventType::ADDSCORE:
            session->SCORE += 100;
            inGameNotification.push_back({"+100", pos, existingTime});
            break;
        case EventType::COLLECT_COINS:
            session->COINS++;
            break;
        case EventType::ADDLIVES:
            session->LIVES++;
            inGameNotification.push_back({"1UP", pos, existingTime});
            break;
        case EventType::MARIO_DIED:
            session->LIVES--;
            break;
        case EventType::RESET_TIMER:
            session->TIMELEFT = 800;
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

    for(int i = 0; i < (int)inGameNotification.size(); i++) {
        std::string s;
        Vector2 pos;
        float waitTime;
        std::tie (s, pos, waitTime) = inGameNotification[i];

        const float floatingVelocity = 96.f;

        waitTime -= GetFrameTime();
        pos.y -= GetFrameTime() * floatingVelocity;
        inGameNotification[i] = make_tuple(s, pos, waitTime);
    }

    while(inGameNotification.size() > 0 && get<2>(inGameNotification.back()) <= 0.f) {
        inGameNotification.pop_back();
    }
}

void HUD::draw() {
    Font font = Program::getInstance().getFont();

    char scoreText[7];
    snprintf(scoreText, sizeof(scoreText), "%06d", session->SCORE);
    std::string coinText = std::to_string(session->COINS);
    std::string worldText = std::to_string(session->WORLD.first) + "-" + std::to_string(session->WORLD.second);
    std::string timeText  = std::to_string(session->TIMELEFT);
    std::string livesText = std::to_string(session->LIVES);

    DrawTextEx(font, PlayScene::isMario ? "MARIO" : "LUIGI", { 20, 14 }, 24, 1, WHITE);
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

    for(int i = 0; i < (int)levelAnnouncement.size(); i++) {
        std::string line = levelAnnouncement[i];

        float size = 34.f;
        float spaceX = 1.f;
        float spaceY = 32.f;
        float shiftY = (Global::WINDOW_HEIGHT - size * levelAnnouncement.size() - spaceY * (levelAnnouncement.size() - 1)) / 2.f;
        
        float posX = (Global::WINDOW_WIDTH - MeasureTextEx(Program::getInstance().getFont(), line.c_str(), size, spaceX).x) / 2.f;
        float posY = shiftY + i * (size + spaceY);
        
        DrawTextEx(Program::getInstance().getFont(), line.c_str(), {posX, posY}, size, spaceX, WHITE);
    }
}

void HUD::addLevelAnnouncement(std::string line) {
    levelAnnouncement.push_back(line);
}

void HUD::clearLevelAnnouncement() {
    levelAnnouncement.clear();
}

const std::vector<std::tuple<std::string, Vector2, float>>& HUD::getInGameNotification(void) const {
    return inGameNotification;
}