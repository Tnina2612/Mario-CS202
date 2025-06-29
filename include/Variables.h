#pragma once
#include "raylib.h"
#include <string>

namespace Global
{
    // The window size
    const int ORIGINAL_WIDTH = 256;
    const int ORIGINAL_HEIGHT = 240;
    const int SCALE_FACTOR = 3;
    const int WINDOW_WIDTH = ORIGINAL_WIDTH * SCALE_FACTOR;
    const int WINDOW_HEIGHT = ORIGINAL_HEIGHT * SCALE_FACTOR;

    // Global Font
    // extern Font mainFont;
    // extern Font consolas;
}

namespace LevelVar {
    enum type {
        Overworld,
        Underground,
        Castle,
        Mushrooms,
        Snow,
        Underwater
    };
    static int ThemeID = 0;
    static Color SkyColor = {92, 148, 252, 255};
};

namespace MenuScreen {
    const Vector2 CursorPos1 = {72, 144};
    const Vector2 CursorPos2 = {72, 160};
}