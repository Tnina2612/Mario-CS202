#pragma once
#include "raylib.h"
#include <string>
using namespace std;

namespace Global
{
    // The window size
    const int ORIGINAL_WIDTH = 256;
    const int ORIGINAL_HEIGHT = 240;
    const int SCALE_FACTOR = 4;
    const int WINDOW_WIDTH = ORIGINAL_WIDTH * SCALE_FACTOR;
    const int WINDOW_HEIGHT = ORIGINAL_HEIGHT * SCALE_FACTOR;

    // Global Font
    // extern Font mainFont;
    // extern Font consolas;
}

enum class EventType {
    ADDSCORE,
    COLLECT_COINS,
    ADDLIVES,
    MARIO_DIED,
    RESET_TIMER
};

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
    static Color SkyColor = {119, 148, 255, 255};
};

namespace MenuScreen {
    const Vector2 CursorPos1 = {72, 144};
    const Vector2 CursorPos2 = {72, 160};
}

namespace CharacterVar {
    const Vector2 position = {10.0f, 100.0f};
    const string MarioSpritePath = "assets/images/mario.png";
    const string LuigiSpritePath = "assets/images/luigi.png";
}

enum CharacterType {
    MARIO,
    LUIGI
};

enum Orientation {
    LEFT,
    RIGHT
};