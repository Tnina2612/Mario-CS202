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
    RESET_TIMER,
    RESET_LIVES,
    RESET_SCORES
};

enum class MusicType {
    OVERWORLD,
    UNDERGROUND,
    CASTLE,
    UNDERWATER
};

enum class SoundType {
    COIN,
    JUMP_SMALL,
    JUMP_SUPER,
    POWERUP,
    POWERDOWN,
    BUMP,
    BREAKBLOCK,
    FIREBALL,
    STOMP,
    KICK,
    ONE_UP,
    FLAGPOLE,
    BOWSER_FIRE,
    BOWSER_FALLS,
    FIREWORKS,
    PIPE,
    VINE,
    WARNING,
    MARIO_DIE,
    GAMEOVER,
    STAGE_CLEAR,
    WORLD_CLEAR,
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
    inline int ThemeID = 0;
    inline Color SkyColor = {146, 148, 255, 255};
    inline Color UndergroundColor = BLACK;
    inline Color BackGroundColor = SkyColor;
    const float animationSpeed = 64.f;
    const Vector2 GoombaSpeed = {32.f, 50.f};
    const Vector2 KoopaSpeed = {-32.f, 0.f};
};

namespace MenuScreen {
    const Vector2 CursorPos1 = {72, 144};
    const Vector2 CursorPos2 = {72, 160};
}

namespace CharacterVar {
    const Vector2 position = {24.f, Global::ORIGINAL_HEIGHT - 32.f - 16.f - 10};
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
    IDLE,
    DEAD,
    CLIMB
};

struct Sprite {
    static Texture2D MarioSprite;
    static Texture2D LuigiSprite;
    static void load() {
        MarioSprite = LoadTexture(CharacterVar::MarioSpritePath.c_str());
        LuigiSprite = LoadTexture(CharacterVar::LuigiSpritePath.c_str());
    }
    static void unload() {
        UnloadTexture(MarioSprite);
        UnloadTexture(LuigiSprite);
    }
};
