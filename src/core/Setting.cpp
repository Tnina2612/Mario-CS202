#include "core/Setting.hpp"
#include "core/Program.hpp"
#include "scenes/SettingScene.hpp"

Setting::Setting() : x(950.0f), y(15.0f), isOn(false) {
    icon = LoadTexture("assets/images/title-scene/setting2.png");
}

Setting::~Setting() {
    UnloadTexture(icon);
}

Setting& Setting::getInstance() {
    static Setting instance;
    return instance;
}

void Setting::draw() {
    DrawTextureEx(icon, {x, y}, 0.0f, 0.15f, WHITE);
}

void Setting::handleInput() {
    if (isClicked()) onClick();
}

bool Setting::isClicked() {
    return CheckCollisionPointRec(GetMousePosition(), {x, y, 386 * 0.15, 386 * 0.15})
           && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void Setting::onClick() {
    if (!isOn) {
        Program::getInstance().pushScene(new SettingScene());
        isOn = true;
    } else {
        Program::getInstance().popScene();
        isOn = false;
    }
}