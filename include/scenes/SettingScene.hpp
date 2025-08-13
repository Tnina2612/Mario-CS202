#pragma once
#include "core/Scene.hpp"
#include "level/Level.hpp"

class SettingScene : public Scene {
private:
    float sliderX_Sound;
    float sliderY_Sound;
    float sliderValue_Sound;
    float sliderX_Music;
    float sliderY_Music;
    float sliderValue_Music;
    Level* level;

public:
    SettingScene(Level* level);
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
};