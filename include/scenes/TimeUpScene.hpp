#pragma once
#include "core/Scene.hpp"

class TimeupScene : public Scene {
private:
    float waitTimer;
    float waitDuration;

public:
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    ~TimeupScene();
};