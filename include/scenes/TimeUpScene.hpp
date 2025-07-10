#pragma once
#include "core/Scene.hpp"

class TimeupScene : public Scene {
public:
    void init() override;
    void handleInput() override;
    void update() override;
    void render() override;
    void cleanup() override;
    ~TimeupScene();
};