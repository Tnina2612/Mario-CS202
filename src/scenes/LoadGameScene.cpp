#include "core/Program.hpp"
#include "core/Setting.hpp"
#include "core/BackButton.hpp"
#include "scenes/LoadGameScene.hpp"
#include "scenes/PlayScene.hpp"
#include "scenes/ComingSoonScene.hpp"
#include "level/TileMap.hpp"
#include "raylib.h"
#include <string>
#include <filesystem>

void LoadGameScene::init() {
    background = new TileMap("world-maps/titleScene/titleScene.txt", nullptr);

    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);
    coin = LoadTexture("assets/images/title-scene/coin.png");
    cursor = LoadTexture("assets/images/title-scene/MenuCursor_transparent.png");

    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        background->draw();
    EndTextureMode();

    playerList = Level::getSavedLevels();
}

void LoadGameScene::handleInput() {
    BackButton::getInstance().handleInput();
    Setting::getInstance().handleInput(nullptr);

    int playerNum = (int)playerList.size();
    if (playerNum == 0) return;

    if (IsKeyPressed(KEY_ENTER)) {
        Program::getInstance().pushScene(new PlayScene(playerList[curRow].second));
    } else if (IsKeyPressed(KEY_DOWN)) {
        curRow = (curRow + 1) % playerNum;
    } else if (IsKeyPressed(KEY_UP)) {
        curRow = ((curRow - 1) % playerNum >= 0) ? (curRow - 1) % playerNum : playerNum - 1;
    }
}

void LoadGameScene::update() {

}

void LoadGameScene::render() {
    DrawTexturePro(renderTexture.texture, 
            Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT},
            Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT},
            Vector2{0, 0}, 0, WHITE);

    Setting::getInstance().draw();
    BackButton::getInstance().draw();
    Font font = Program::getInstance().getFont();
    
    DrawTextEx(font, "PLAYERS", {120, initialPos - 65}, 40, 1, WHITE);
    DrawTextEx(font, "POINTS", {445, initialPos - 65}, 40, 1, WHITE);
    DrawTextEx(font, "WOLRD", {730, initialPos - 65}, 40, 1, WHITE);

    if (!playerList.empty()) {
        DrawTextureEx(cursor, {50, initialPos + curRow * 50}, 0.0f, 4.0f, WHITE);
    }

    float cursorPos = initialPos;
    for (auto player : playerList) {
        DrawTextEx(font, player.first.c_str(), {120, cursorPos}, 34, 1, WHITE);
        cursorPos += 50;
    }


}

LoadGameScene::~LoadGameScene() {
    if (background) {
        delete background;
        background = nullptr;
    }

    UnloadRenderTexture(renderTexture);
    UnloadTexture(coin);
    UnloadTexture(cursor);
}