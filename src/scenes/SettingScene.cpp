#include "core/Variables.hpp"
#include "core/Program.hpp"
#include "core/Setting.hpp"
#include "core/InputField.hpp"
#include "scenes/SettingScene.hpp"
#include "scenes/TitleScene.hpp"
#include "scenes/PlayScene.hpp"
#include "core/SoundManager.hpp"
#include "core/MusicManager.hpp"
#include "raylib.h"
#include "raymath.h"

SettingScene::SettingScene(Level* level) : level(level) {

}

void SettingScene::init() {
    sliderX_Sound = 512.0f;
    sliderY_Sound = 575.0f;
    sliderValue_Sound = 0.5f;
    sliderX_Music = 512.0f;
    sliderY_Music = 725.0f;
    sliderValue_Music = 0.5f;
    isReleaseSound = true;
    isReleaseMusic = true;
}

void SettingScene::handleInput() {
    Setting::getInstance().handleInput(level);

    Vector2 mouse = GetMousePosition();
    Vector2 textSize1 = MeasureTextEx(Program::getInstance().getFont(), "SAVE GAME", 34.0f, 1.0f);
    Vector2 textSize2 = MeasureTextEx(Program::getInstance().getFont(), "RESTART", 34.0f, 1.0f);
    Vector2 textSize3 = MeasureTextEx(Program::getInstance().getFont(), "MAIN MENU", 34.0f, 1.0f);
    float x1 = (Global::WINDOW_WIDTH - textSize1.x) / 2.0f;
    float x2 = (Global::WINDOW_WIDTH - textSize2.x) / 2.0f;
    float x3 = (Global::WINDOW_WIDTH - textSize3.x) / 2.0f;

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(mouse, {x1, 250, textSize1.x, textSize1.y})) {
            // Handle SAVE GAME click
            if (level != nullptr && !InputField::currentSessionName.empty()) {
                level->saveGame(InputField::currentSessionName);
            }
        } else if (CheckCollisionPointRec(mouse, {x2, 330, textSize2.x, textSize2.y})) {
            // Handle RESTART click
        } else if (CheckCollisionPointRec(mouse, {x3, 410, textSize3.x, textSize3.y})) {
            Program::getInstance().pushScene(new TitleScene());
            Setting::getInstance().toggle(false);
        }
    }

    if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        isReleaseSound = isReleaseMusic = true;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) 
        && CheckCollisionPointCircle(mouse, {sliderX_Sound, sliderY_Sound}, 13)) {
        isReleaseSound = false;
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) 
        && CheckCollisionPointCircle(mouse, {sliderX_Music, sliderY_Music}, 13)) {
        isReleaseMusic = false;
    }

    sliderX_Sound = 362.0f + sliderValue_Sound * 300;
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !isReleaseSound) {
        float mouseX = Clamp(mouse.x, 362, 362 + 300);
        sliderValue_Sound = (mouseX - 362) / 300;
        
        SoundManager::getInstance().setMasterVolume(sliderValue_Sound);
    }

    sliderX_Music = 362.0f + sliderValue_Music * 300;
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !isReleaseMusic) {
        float mouseX = Clamp(mouse.x, 362, 362 + 300);
        sliderValue_Music = (mouseX - 362) / 300;
        
        MusicManager::getInstance().setMusicVolume(sliderValue_Music);
    }
}

void SettingScene::update() {
    
}

void SettingScene::render() {
    ClearBackground(BLACK);

    Font font = Program::getInstance().getFont();
    Vector2 mouse = GetMousePosition();

    Vector2 textSize1 = MeasureTextEx(font, "SAVE GAME", 34.0f, 1.0f);
    Vector2 textSize2 = MeasureTextEx(font, "RESTART", 34.0f, 1.0f);
    Vector2 textSize3 = MeasureTextEx(font, "MAIN MENU", 34.0f, 1.0f);
    Vector2 textSize4 = MeasureTextEx(font, "SOUND VOLUME", 34.0f, 1.0f);
    Vector2 textSize5 = MeasureTextEx(font, "MUSIC VOLUME", 34.0f, 1.0f);
    float x1 = (Global::WINDOW_WIDTH - textSize1.x) / 2.0f;
    float x2 = (Global::WINDOW_WIDTH - textSize2.x) / 2.0f;
    float x3 = (Global::WINDOW_WIDTH - textSize3.x) / 2.0f;
    float x4 = (Global::WINDOW_WIDTH - textSize4.x) / 2.0f;
    float x5 = (Global::WINDOW_WIDTH - textSize5.x) / 2.0f;

    Color color1 = CheckCollisionPointRec(mouse, {x1, 250, textSize1.x, textSize1.y}) ? Color{151, 77, 4, 255} : WHITE;
    Color color2 = CheckCollisionPointRec(mouse, {x2, 330, textSize2.x, textSize2.y}) ? Color{151, 77, 4, 255} : WHITE;
    Color color3 = CheckCollisionPointRec(mouse, {x3, 410, textSize3.x, textSize3.y}) ? Color{151, 77, 4, 255} : WHITE;

    DrawTextEx(font, "SAVE GAME", {x1, 250}, 34.0f, 1.0f, color1);
    DrawTextEx(font, "RESTART", {x2, 330}, 34.0f, 1.0f, color2);
    DrawTextEx(font, "MAIN MENU", {x3, 410}, 34.0f, 1.0f, color3);

    DrawTextEx(font, "SOUND VOLUME", {x4, 490}, 34.0f, 1.0f, WHITE);
    DrawRectangleRounded({362, 570, 300, 10}, 1.0f, 10, WHITE);
    DrawCircle(sliderX_Sound, sliderY_Sound, 13, WHITE);
    DrawCircleLines(sliderX_Sound, sliderY_Sound, 14, BLACK);
    DrawCircleLines(sliderX_Sound, sliderY_Sound, 15, BLACK);
    DrawCircleLines(sliderX_Sound, sliderY_Sound, 16, BLACK);
    DrawCircleLines(sliderX_Sound, sliderY_Sound, 17, BLACK);
    DrawCircleLines(sliderX_Sound, sliderY_Sound, 18, BLACK);
    DrawCircleLines(sliderX_Sound, sliderY_Sound, 19, BLACK);

    DrawTextEx(font, "MUSIC VOLUME", {x5, 640}, 34.0f, 1.0f, WHITE);
    DrawRectangleRounded({362, 720, 300, 10}, 1.0f, 10, WHITE);
    DrawCircle(sliderX_Music, sliderY_Music, 13, WHITE);
    DrawCircleLines(sliderX_Music, sliderY_Music, 14, BLACK);
    DrawCircleLines(sliderX_Music, sliderY_Music, 15, BLACK);
    DrawCircleLines(sliderX_Music, sliderY_Music, 16, BLACK);
    DrawCircleLines(sliderX_Music, sliderY_Music, 17, BLACK);
    DrawCircleLines(sliderX_Music, sliderY_Music, 18, BLACK);
    DrawCircleLines(sliderX_Music, sliderY_Music, 19, BLACK);

    Setting::getInstance().draw();
}