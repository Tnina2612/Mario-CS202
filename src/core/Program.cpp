#include "core/Program.hpp"
#include "core/Variables.hpp"
#include "core/SoundManager.hpp"
#include "core/MusicManager.hpp"
#include "scenes/TitleScene.hpp"
#include "scenes/PlayScene.hpp"

Texture2D Sprite::LuigiSprite;
Texture2D Sprite::MarioSprite;

Program::Program() : running(true), nextScene(nullptr) {
    // Khởi tạo Raylib
    SetConfigFlags(FLAG_MSAA_4X_HINT);  
    InitWindow(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, "Super Mario Bros. 1985");
    icon = LoadImage("assets/images/title-scene/icon.png");
    SetWindowIcon(icon);
    InitAudioDevice();
    SetTargetFPS(120);

    font = LoadFont("assets/fonts/super-mario-bros-nes.otf");
    hud = new HUD(&session);
    SoundManager::getInstance().loadSounds();
    MusicManager::getInstance().loadMusic();
}

Program::~Program() {
    // Free resources
    while (!sceneStack.empty()) {
        delete sceneStack.top();
        sceneStack.pop();
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

void Program::pushScene(Scene* scene) {
    nextScene = scene;
}

void Program::popScene() {
    sceneStack.pop();
}

void Program::run() { // Game loop
    pushScene(new TitleScene());
    Sprite::load();
    while (!WindowShouldClose() && running) {
        // Handle immediate scene changes at the start of each frame
        if (nextScene != nullptr) {
            sceneStack.push(nextScene);
            nextScene->init();
            nextScene = nullptr;
        }

        Scene* currentScene = nullptr;
        if (!sceneStack.empty()) {
            currentScene = sceneStack.top();
        }

        // Update the current scene
        if (currentScene != nullptr) {
            currentScene->handleInput();
            currentScene->update();

            MusicManager::getInstance().updateMusic();
            
            BeginDrawing();
                ClearBackground(RAYWHITE);
                currentScene->render();
            EndDrawing();
        }
    }
    Sprite::unload();
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