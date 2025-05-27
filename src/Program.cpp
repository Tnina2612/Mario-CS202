#include "Program.h"
#include "Variables.h"
// #include "Items/Button.h"
// #include "Items/InputField.h"
#include "Pages/MainPage.h"

Program::Program() {
    // Khởi tạo Raylib
    SetConfigFlags(FLAG_MSAA_4X_HINT);  
    InitWindow(Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT, "Super Mario Bros.");
    InitAudioDevice();
    SetTargetFPS(60);

    // // Using custom fonts
    // Global::mainFont = LoadFontEx("../assets/fonts/Montserrat-Regular.ttf", 100, 0, 0); 
    // Global::consolas = LoadFont("../assets/fonts/Consolas.TTF");
    // SetTextureFilter(Global::mainFont.texture, TEXTURE_FILTER_TRILINEAR);

    // // Using custom music
    // kigeki = LoadMusicStream("../assets/sounds/Kigeki_SpyxFamilyED_Lofi.ogg");
    // kigeki.looping = true;
    // PlayMusicStream(kigeki);

    running = true;

    // Push MainPage into stack
    pushPage(std::make_unique<MainPage>(this));
}

Program::~Program() {
    // Free resources
    // UnloadFont(Global::mainFont);
    // UnloadMusicStream(kigeki);
    CloseAudioDevice();
    CloseWindow();
}

void Program::run() { // Game loop
    while (!WindowShouldClose() && !pages.empty()) {
        // UpdateMusicStream(kigeki);
        float deltaTime = GetFrameTime();

        // Handle input first
        if (!pages.empty()) {
            pages.top()->handleInput();
        }

        // Recheck the stack after handleInput (it maybe changed)
        if (pages.empty()) {
            break;
        }

        // Get the currentPage from the new stack
        Page* currentPage = pages.top().get();

        // Update and draw
        currentPage->update(deltaTime);
        currentPage->draw();
    }
}

void Program::pushPage(std::unique_ptr<Page> page) {
    pages.push(std::move(page));
}

void Program::popPage() {
    if (!pages.empty()) {
        pages.pop();
    }
}

bool Program::isEmpty() const {
    return pages.empty();
}