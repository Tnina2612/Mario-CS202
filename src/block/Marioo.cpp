#include "raylib.h"
#include "BlockFactory.h"
#include "Level.h"

int main() {
    InitWindow(800, 600, "Mario 1985 - Block Scene");
    SetTargetFPS(60);

    BlockFactory::Init();
    Level level;

    float y = 400;
    for (int i = 0; i < 10; ++i) {
        float x = 100 + i * 32;
        if (i % 3 == 0)
            level.AddBlock(BlockFactory::CreateBlock("Brick", x, y));
        else if (i % 3 == 1)
            level.AddBlock(BlockFactory::CreateBlock("Question", x, y));
        else
            level.AddBlock(BlockFactory::CreateBlock("Invisible", x, y));
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        level.Draw();
        EndDrawing();
    }

    BlockFactory::CleanUp();
    CloseWindow();
    return 0;
}
