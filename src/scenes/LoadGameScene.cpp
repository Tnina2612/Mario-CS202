#include "core/Program.hpp"
#include "core/Setting.hpp"
#include "core/BackButton.hpp"
#include "scenes/LoadGameScene.hpp"
#include "scenes/PlayScene.hpp"
#include "scenes/ComingSoonScene.hpp"
#include "level/TileMap.hpp"
#include "raylib.h"
#include <string>

void LoadGameScene::init() {
    background = new TileMap("world-maps/titleScene/titleScene.txt");

    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);
    coin = LoadTexture("assets/images/title-scene/coin.png");
    cursor = LoadTexture("assets/images/title-scene/MenuCursor_transparent.png");

    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        background->draw();
    EndTextureMode();

    // playerList = ???;
}

void LoadGameScene::handleInput() {
    BackButton::getInstance().handleInput();
    Setting::getInstance().handleInput(nullptr);

    int playerNum = (int)playerList.size();
    if (playerNum == 0) return;

    if (IsKeyPressed(KEY_ENTER)) {
        
    } else if (IsKeyPressed(KEY_DOWN)) {
        curRow = (curRow + 1) % playerNum;
    } else if (IsKeyPressed(KEY_UP)) {
        curRow = ((curRow - 1) % playerNum >= 0) ? (curRow - 1) % playerNum : playerNum - 1;
    }

    Setting::getInstance().handleInput(nullptr);
    BackButton::getInstance().handleInput();
}

void LoadGameScene::update() {

}

void LoadGameScene::render() {
    DrawTexturePro(renderTexture.texture, 
            Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT},
            Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT},
            Vector2{0, 0}, 0, WHITE);

    Font font = Program::getInstance().getFont();
    
    DrawTextEx(font, "PLAYERS", {100, initialPos - 35}, 40, 1, WHITE);
    DrawTextEx(font, "POINTS", {445, initialPos - 35}, 40, 1, WHITE);
    DrawTextEx(font, "WOLRD", {750, initialPos - 35}, 40, 1, WHITE);

    if (!playerList.empty()) {
        DrawTextureEx(cursor, {100, initialPos + curRow * 40}, 0.0f, 4.0f, WHITE);
    }

    float cursorPos = initialPos;
    for (auto player : playerList) {
        DrawTextEx(font, player.first.c_str(), {170, cursorPos}, 34, 1, WHITE);
        cursorPos += 40;
    }

    Setting::getInstance().draw();
    BackButton::getInstance().draw();
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