#pragma once

class Scene {
public:
    virtual void init() = 0;
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void render() = 0;
    virtual ~Scene() = default;
};