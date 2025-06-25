#pragma once
#include "raylib.h"

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

namespace MenuScreen {
    const Vector2 CursorPos1 = {72, 144};
    const Vector2 CursorPos1 = {72, 160};
}