#include "core/Program.hpp"
#include "scenes/TitleScene.hpp"
#include "scenes/PlayScene.hpp"
#include "block/Block.h"
#include "raylib.h"

void TitleScene::init() {
    background = new TileMap("world-maps/titleScene/titleScene.txt");

    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);
    coin = LoadTexture("assets/images/title-scene/coin.png");
    logo = LoadTexture("assets/images/title-scene/logo.png");
    copyright = LoadTexture("assets/images/title-scene/copyright.png");
    cursor = LoadTexture("assets/images/title-scene/MenuCursor_transparent.png");

    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        background->draw();
    EndTextureMode();
}

void TitleScene::handleInput() {
    if (IsKeyPressed(KEY_ENTER)) {
        Program::getInstance().changeScene(new PlayScene());
    } else if (IsKeyPressed(KEY_DOWN)) {
        curMode = (curMode + 1) % 2;
    } else if (IsKeyPressed(KEY_UP)) {
        curMode = (curMode + 3) % 2;
    }
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

    DrawTextEx(font, "MARIO", { 80, 14 }, 34, 1, WHITE);
    DrawTextEx(font, "COINS", { 360, 14 }, 34, 1, WHITE);
    DrawTextEx(font, "WORLD", { 600, 14 }, 34, 1, WHITE);
    DrawTextEx(font, "TIME",  { 830, 14 }, 34, 1, WHITE);

    DrawTextEx(font, "000400", { 80, 45 }, 34, 1, WHITE);
    DrawTextureEx(coin, {360, 49}, 0.0f, 3.5f, WHITE);
    DrawText("x", 380, 43, 40, WHITE);
    DrawTextEx(font, "02", { 405, 45 }, 34, 1, WHITE);;
    DrawTextEx(font, "1-1", { 630, 45 }, 34, 1, WHITE);
    
    DrawTextureEx(logo, {150, 80}, 0.0f, 0.5f, WHITE);
    DrawTextureEx(copyright, {445, 441}, 0.0f, 1.0f, WHITE);
    DrawTextEx(font, "1985 NINTENDO", {478, 440}, 34, 1, {255, 206, 180, 255});
    
    DrawTextureEx(cursor, {280, (float)cursorPos[curMode]}, 0.0f, 4.0f, WHITE);
    DrawTextEx(font, "1 PLAYER GAME", {360, 580}, 34, 1, WHITE);
    DrawTextEx(font, "2 PLAYER GAME", {360, 640}, 34, 1, WHITE);
    DrawTextEx(font, "TOP- 000000", {384, 720}, 34, 1, WHITE);
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