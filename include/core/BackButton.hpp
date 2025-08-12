#pragma once

class BackButton {
private:
    float x;
    float y;

    BackButton();

public:
    BackButton(const BackButton&) = delete;
    void operator=(const BackButton&) = delete;

    static BackButton& getInstance(); 

    void draw();
    void handleInput();
    bool isHovered();
    bool isClicked();
    void onClick();
};