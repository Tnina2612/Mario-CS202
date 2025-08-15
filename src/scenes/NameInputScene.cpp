#include "core/Program.hpp"
#include "core/Setting.hpp"
#include "core/BackButton.hpp"
#include "scenes/NameInputScene.hpp"
#include "scenes/DeathScene.hpp"
#include "level/TileMap.hpp"
#include "raylib.h"
#include <string>

void NameInputScene::init() {
    background = new TileMap("world-maps/titleScene/titleScene.txt", nullptr);
    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);

    inputField = new InputField(300.0f, 350.0f, 400.0f, 50.0f);

    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        background->draw();
    EndTextureMode();
}

void NameInputScene::handleInput() {
    BackButton::getInstance().handleInput();
    Setting::getInstance().handleInput(nullptr);
    inputField->handleInput();

    if (IsKeyPressed(KEY_ENTER)) {
        InputField::currentSessionName = inputField->getText();
        Program::getInstance().pushScene(new DeathScene());
    }
}

void NameInputScene::update() {
    float deltaTime = GetFrameTime();
    inputField->update(deltaTime);
}

void NameInputScene::render() {
    DrawTexturePro(renderTexture.texture, 
            Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT},
            Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT},
            Vector2{0, 0}, 0, WHITE);

    BackButton::getInstance().draw();
    Setting::getInstance().draw();

    char text[] = "ENTER NAME FOR THIS SESSION";
    Vector2 textSize = MeasureTextEx(Program::getInstance().getFont(), text, 34.0f, 1.0f);
    DrawTextEx(Program::getInstance().getFont(), text, {(Global::WINDOW_WIDTH - textSize.x)/2.0f, 300}, 34.0f, 1.0f, WHITE);

    inputField->draw();

    char text2[] = "You need to manually save the session";
    Vector2 textSize2 = MeasureTextEx(Program::getInstance().getFont(), text2, 25.0f, 1.0f);
    DrawTextEx(Program::getInstance().getFont(), text2, {(Global::WINDOW_WIDTH - textSize2.x)/2.0f, 500}, 25.0f, 1.0f, WHITE);

    char text3[] = "in Setting. Saved sessions are stored";
    Vector2 textSize3 = MeasureTextEx(Program::getInstance().getFont(), text3, 25.0f, 1.0f);
    DrawTextEx(Program::getInstance().getFont(), text3, {(Global::WINDOW_WIDTH - textSize3.x)/2.0f, 550}, 25.0f, 1.0f, WHITE);

    char text4[] = "in Load Game Option.";
    Vector2 textSize4 = MeasureTextEx(Program::getInstance().getFont(), text4, 25.0f, 1.0f);
    DrawTextEx(Program::getInstance().getFont(), text4, {(Global::WINDOW_WIDTH - textSize4.x)/2.0f, 600}, 25.0f, 1.0f, WHITE);
}

NameInputScene::~NameInputScene() {
    if (background) {
        delete background;
        background = nullptr;
    }

    delete inputField;
    inputField = nullptr;

    UnloadRenderTexture(renderTexture);
}