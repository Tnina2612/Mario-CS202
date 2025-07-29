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
    const int TILE_SIZE = 16;

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
    const Vector2 position = {24.f, Global::ORIGINAL_HEIGHT - 32.f - 16.f};
    const string MarioSpritePath = "./assets/images/sprite-sheets/mario.png";
    const string LuigiSpritePath = "./assets/images/sprite-sheets/luigi.png";
}

enum CharacterType {
    MARIO,
    LUIGI
};

enum Orientation {
    LEFT,
    RIGHT
};

enum CharacterState {
    SMALL,
    SUPER,
    FIRE
};

enum Behavior {
    MOVE,
    JUMP,
    BRAKE,
    DUCK,
    THROW,
    IDLE
};
