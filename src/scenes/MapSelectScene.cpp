#include "core/Program.hpp"
#include "core/Setting.hpp"
#include "core/BackButton.hpp"
#include "scenes/MapSelectScene.hpp"
#include "scenes/PlayScene.hpp"
#include "scenes/DeathScene.hpp"
#include "scenes/ComingSoonScene.hpp"
#include "level/TileMap.hpp"
#include "raylib.h"
#include <string>

void MapSelectScene::init() {
    background = new TileMap("world-maps/titleScene/titleScene.txt", nullptr);

    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);
    coin = LoadTexture("assets/images/title-scene/coin.png");
    cursor = LoadTexture("assets/images/title-scene/MenuCursor_transparent.png");

    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        background->draw();
    EndTextureMode();
}

void MapSelectScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        if (curModeRow <= 0 && curModeCol < 3) {
            Program::getInstance().pushScene(new PlayScene(to_string(curModeRow + 1) + "-" + to_string(curModeCol + 1)));
        } else {
            Program::getInstance().pushScene(new ComingSoonScene());
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        curModeRow = (curModeRow + 1) % 8;
    } else if (IsKeyPressed(KEY_UP)) {
        curModeRow = ((curModeRow - 1) % 8 >= 0) ? (curModeRow - 1) % 8 : 7;
    } else if (IsKeyPressed(KEY_RIGHT)) {
        curModeCol = (curModeCol + 1) % 4;
    } else if (IsKeyPressed(KEY_LEFT)) {
        curModeCol = ((curModeCol - 1) % 4 >= 0) ? (curModeCol - 1) % 4 : 3;
    }

    Setting::getInstance().handleInput(nullptr);
    BackButton::getInstance().handleInput();
}

void MapSelectScene::update() {

}

void MapSelectScene::render() {
    DrawTexturePro(renderTexture.texture, 
            Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT},
            Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT},
            Vector2{0, 0}, 0, WHITE);

    // Draw game session
    Font font = Program::getInstance().getFont();
    
    DrawTextureEx(cursor, {(float)cursorCol[curModeCol], (float)cursorRow[curModeRow]}, 0.0f, 4.0f, WHITE);
    DrawTextEx(font, "1-1", {170, 150}, 34, 1, WHITE);
    DrawTextEx(font, "1-2", {370, 150}, 34, 1, WHITE);
    DrawTextEx(font, "1-3", {570, 150}, 34, 1, WHITE);
    DrawTextEx(font, "1-4", {770, 150}, 34, 1, WHITE);
    DrawTextEx(font, "2-1", {170, 220}, 34, 1, WHITE);
    DrawTextEx(font, "2-2", {370, 220}, 34, 1, WHITE);
    DrawTextEx(font, "2-3", {570, 220}, 34, 1, WHITE);
    DrawTextEx(font, "2-4", {770, 220}, 34, 1, WHITE);
    DrawTextEx(font, "3-1", {170, 290}, 34, 1, WHITE);
    DrawTextEx(font, "3-2", {370, 290}, 34, 1, WHITE);
    DrawTextEx(font, "3-3", {570, 290}, 34, 1, WHITE);
    DrawTextEx(font, "3-4", {770, 290}, 34, 1, WHITE);
    DrawTextEx(font, "4-1", {170, 360}, 34, 1, WHITE);
    DrawTextEx(font, "4-2", {370, 360}, 34, 1, WHITE);
    DrawTextEx(font, "4-3", {570, 360}, 34, 1, WHITE);
    DrawTextEx(font, "4-4", {770, 360}, 34, 1, WHITE);
    DrawTextEx(font, "5-1", {170, 430}, 34, 1, WHITE);
    DrawTextEx(font, "5-2", {370, 430}, 34, 1, WHITE);
    DrawTextEx(font, "5-3", {570, 430}, 34, 1, WHITE);
    DrawTextEx(font, "5-4", {770, 430}, 34, 1, WHITE);
    DrawTextEx(font, "6-1", {170, 500}, 34, 1, WHITE);
    DrawTextEx(font, "6-2", {370, 500}, 34, 1, WHITE);
    DrawTextEx(font, "6-3", {570, 500}, 34, 1, WHITE);
    DrawTextEx(font, "6-4", {770, 500}, 34, 1, WHITE);
    DrawTextEx(font, "7-1", {170, 570}, 34, 1, WHITE);
    DrawTextEx(font, "7-2", {370, 570}, 34, 1, WHITE);
    DrawTextEx(font, "7-3", {570, 570}, 34, 1, WHITE);
    DrawTextEx(font, "7-4", {770, 570}, 34, 1, WHITE);
    DrawTextEx(font, "8-1", {170, 640}, 34, 1, WHITE);
    DrawTextEx(font, "8-2", {370, 640}, 34, 1, WHITE);
    DrawTextEx(font, "8-3", {570, 640}, 34, 1, WHITE);
    DrawTextEx(font, "8-4", {770, 640}, 34, 1, WHITE);

    Setting::getInstance().draw();
    BackButton::getInstance().draw();
}

MapSelectScene::~MapSelectScene() {
    if (background) {
        delete background;
        background = nullptr;
    }

    UnloadRenderTexture(renderTexture);
    UnloadTexture(coin);
    UnloadTexture(cursor);
}