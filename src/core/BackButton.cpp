#include "core/Program.hpp"
#include "core/BackButton.hpp"

BackButton::BackButton() : x(20.0f), y(15.0f) {

}

BackButton& BackButton::getInstance() {
    static BackButton instance;
    return instance;
}

void BackButton::draw() {
    DrawTextEx(Program::getInstance().getFont(), "BACK", {x, y}, 34.0f, 1.0f, WHITE);
}

void BackButton::handleInput() {
    if (isClicked()) onClick();
}

bool BackButton::isClicked() {
    Vector2 rec = MeasureTextEx(Program::getInstance().getFont(), "BACK", 34.0f, 1.0f);
    return CheckCollisionPointRec(GetMousePosition(), {x, y, rec.x, rec.y})
           && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void BackButton::onClick() {
    Program::getInstance().popScene();
}