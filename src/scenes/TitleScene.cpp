#include "core/Program.hpp"
#include "core/Setting.hpp"
#include "scenes/TitleScene.hpp"
#include "scenes/PlayScene.hpp"
#include "scenes/NameInputScene.hpp"
#include "scenes/MapSelectScene.hpp"
#include "scenes/LoadGameScene.hpp"
#include "block/Block.h"
#include "core/MusicManager.hpp"
#include "raylib.h"

void TitleScene::init() {
    background = new TileMap("world-maps/titleScene/titleScene.txt", nullptr);
    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);
    coin = LoadTexture("assets/images/title-scene/coin.png");
    logo = LoadTexture("assets/images/title-scene/logo.png");
    copyright = LoadTexture("assets/images/title-scene/copyright.png");
    cursor = LoadTexture("assets/images/title-scene/MenuCursor_transparent.png");

    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        background->draw();
    EndTextureMode();

    MusicManager::getInstance().playMusic(MusicType::OVERWORLD);

    Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
    Program::getInstance().getHUD().onNotify(EventType::RESET_LIVES);
    Program::getInstance().getHUD().onNotify(EventType::RESET_SCORES);
}

void TitleScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        switch (curMode) {
            case 0:
                Program::getInstance().pushScene(new NameInputScene());
                PlayScene::is2players = false;
                break;
            case 1:
                Program::getInstance().pushScene(new NameInputScene());
                PlayScene::is2players = true;
                break;
            case 2:
                Program::getInstance().pushScene(new LoadGameScene());
                break;
            case 3:
                Program::getInstance().pushScene(new MapSelectScene());
                break;
            default:
                break;
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        curMode = (curMode + 1) % 4;
    } else if (IsKeyPressed(KEY_UP)) {
        curMode = ((curMode - 1) % 4 >= 0) ? (curMode - 1) % 4 : 3;
    }

    Setting::getInstance().handleInput(nullptr);
}

void TitleScene::update() {
}

void TitleScene::render() {
    DrawTexturePro(renderTexture.texture, 
        Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT},
        Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT},
        Vector2{0, 0}, 0, WHITE);

    // Draw game session
    Font font = Program::getInstance().getFont();

    DrawTextEx(font, "MARIO", { 40, 14 }, 34, 1, WHITE);
    DrawTextEx(font, "COINS", { 320, 14 }, 34, 1, WHITE);
    DrawTextEx(font, "WORLD", { 560, 14 }, 34, 1, WHITE);
    DrawTextEx(font, "TIME",  { 790, 14 }, 34, 1, WHITE);

    DrawTextEx(font, "000400", { 40, 45 }, 34, 1, WHITE);
    DrawTextureEx(coin, {320, 49}, 0.0f, 3.5f, WHITE);
    DrawText("x", 340, 43, 40, WHITE);
    DrawTextEx(font, "02", { 365, 45 }, 34, 1, WHITE);
    DrawTextEx(font, "1-1", { 590, 45 }, 34, 1, WHITE);
    
    DrawTextureEx(logo, {150, 80}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(copyright, {445, 441}, 0.0f, 1.0f, WHITE);
    DrawTextEx(font, "1985 NINTENDO", {478, 440}, 34, 1, {255, 206, 180, 255});
    
    DrawTextureEx(cursor, {280, (float)cursorPos[curMode]}, 0.0f, 4.0f, WHITE);
    DrawTextEx(font, "1 PLAYER GAME", {360, (float)cursorPos[0]}, 34, 1, WHITE);
    DrawTextEx(font, "2 PLAYER GAME", {360, (float)cursorPos[1]}, 34, 1, WHITE);
    DrawTextEx(font, "LOAD GAME", {360, (float)cursorPos[2]}, 34, 1, WHITE);
    DrawTextEx(font, "MAP SELECT", {360, (float)cursorPos[3]}, 34, 1, WHITE);
    DrawTextEx(font, "TOP- 000000", {360, 780}, 34, 1, WHITE);

    Setting::getInstance().draw();
}

TitleScene::~TitleScene() {
    if (background) {
        delete background;
        background = nullptr;
    }

    UnloadRenderTexture(renderTexture);
    UnloadTexture(coin);
    UnloadTexture(logo);
    UnloadTexture(copyright);
    UnloadTexture(cursor);
}