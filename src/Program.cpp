#include "Program.h"
#include "Variables.h"
// #include "Items/Button.h"
// #include "Items/InputField.h"

Program::Program() {
    // Khởi tạo Raylib
    SetConfigFlags(FLAG_MSAA_4X_HINT);  
    InitWindow(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, "Super Mario Bros.");
    InitAudioDevice();
    SetTargetFPS(120);
    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);
    level = std::make_shared<Level>();

    running = true;
}

Program::~Program() {
    // Free resources
    // UnloadFont(Global::mainFont);
    // UnloadMusicStream(kigeki);
    CloseAudioDevice();
    CloseWindow();
}

void Program::run() { // Game loop
    while (!WindowShouldClose()) {
        // UpdateMusicStream(kigeki);
        float deltaTime = GetFrameTime();

        // Update and draw
        // currentPage->update(deltaTime);
        // currentPage->draw();

        /*Phát: test the level drawing, erase these lines of code if you want*/
        {BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        level->draw();
        EndTextureMode();
        
        BeginDrawing();
        DrawTexturePro(renderTexture.texture, 
            Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT},
            Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT},
            Vector2{0, 0}, 0, WHITE);
        EndDrawing();}
    }
}