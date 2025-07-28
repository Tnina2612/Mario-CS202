#pragma once
#include"../../assets/images/Coordinate.h"

class Animation {
protected:
    float scale;
    vector<Rectangle> frames;
    int currentFrame;
    
    float frameTime;
    const float defaultFrameTime = 0.1f; // Default frame time if not specified
public:
    Texture2D sprite;
    Animation();
    Animation(const vector<Rectangle>& frames);
    Animation(const vector<Rectangle>& frames, const Texture2D& sprite, float frameTime = 0.2f, float scale = 1.0f);
    void setFrames(const vector<Rectangle>& newFrames);
    void update(float deltaTime, int startFrame = 0, int size = -1);
    void draw(Vector2 position) const;
    void reset();
    void setScale(float scale);
    virtual ~Animation() = default;
};