#pragma once

#include "raylib.h"
#include <string>

class InputField {
private:
    Rectangle box;
    std::string inputText;
    bool isActive;
    int cursorPos = 0;
    float blinkTimer = 0.0f;
    bool showCursor = true;
    float blinkInterval = 0.5f;
    float scrollOffset = 0.0f;

public:
    InputField(float x, float y, float width, float height);

    void handleInput();
    void draw();
    void update(float deltaTime);

    void updateCursorPosition(int mouseX);
    void UpdateScrollOffset();

    std::string getText() const { 
        return inputText; 
    }
    void clearText() { 
        inputText.clear(); 
    }

    bool IsActive();
    void setActive(bool state);
};