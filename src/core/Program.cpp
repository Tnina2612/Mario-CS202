#include "core/Program.h"
#include "Variables.h"
#include "scenes/TitleScene.hpp"
#include "scenes/PlayScene.hpp"

Program::Program() : running(true), currentScene(nullptr), nextScene(nullptr) {
    // Khởi tạo Raylib
    SetConfigFlags(FLAG_MSAA_4X_HINT);  
    InitWindow(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, "Super Mario Bros. 1985");
    icon = LoadImage("assets/images/title-scene/icon.png");
    SetWindowIcon(icon);
    InitAudioDevice();
    SetTargetFPS(120);
    font = LoadFont("assets/fonts/super-mario-bros-nes.otf");
    hud = new HUD(&session);
}

Program::~Program() {
    // Free resources
    if (currentScene) {
        delete currentScene;
        currentScene = nullptr;
    }
    if (nextScene) {
        delete nextScene;
        nextScene = nullptr;
    }
    if (hud) {
        delete hud;
        hud = nullptr;
    }
    
    UnloadFont(font);
    CloseAudioDevice();
    UnloadImage(icon);
    CloseWindow();
}

Program& Program::getInstance() {
    static Program instance;
    return instance;
}

void Program::changeScene(Scene* scene) {
    nextScene = scene;
}

void Program::run() { // Game loop
    changeScene(new TitleScene());

    while (!WindowShouldClose() && running) {
        if (nextScene != nullptr) {
            if (currentScene) {
                delete currentScene;
                currentScene = nullptr; 
            }
            currentScene = nextScene;
            currentScene->init();
            nextScene = nullptr;
        }

        if (currentScene) {
            currentScene->handleInput();
            currentScene->update();
            
            BeginDrawing();
            ClearBackground(RAYWHITE);
            currentScene->render();
            EndDrawing();
        }   
    }
}

Font Program::getFont() {
    return font;
}

GameSession& Program::getSession() {
    return session;
}

HUD& Program::getHUD() {
    return *hud;
}