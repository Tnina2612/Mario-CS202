#pragma once
#include"../../assets/images/Coordinate.h"
#include<entities/AnimationVectorTextureFlyweight.hpp>
#include<core/Variables.hpp>

class Animation {
protected:
    float scale;
    vector<Rectangle> frames;
    int currentFrame;
    int scaleFrame = 0;
    float blinkingTime = 0.0f;

    float frameTime;
    const float defaultFrameTime = 0.1f; // Default frame time if not specified
    Texture2D sprite;
public:
    Animation();
    Animation(const vector<Rectangle>& frames);
    Animation(const vector<Rectangle>& frames, const Texture2D& sprite, float frameTime = 0.2f, float scale = 1.0f);
    int getCurrentFrame()const {
        return currentFrame;
    }
    Rectangle getCurrentRectangle() const {
        return frames[currentFrame];
    }
    void setFrames(const vector<Rectangle>& newFrames);
    void resetCurrentFrame();
    void update(float deltaTime, int startFrame = 0, int size = -1);
    bool update(const vector<float>& scales, int currentFrame, float scaleTime = 0.2, float deltaTime = GetFrameTime());
    void draw(Vector2 position) const;
    void reset();
    void setScale(float scale);
    float getScale() const;
    void setSprite(const Texture2D& sprite);
    virtual ~Animation() = default;
    void updateBlinking(float deltaTime, bool& onAnimation);
};

class AnimationVectorTexture {
private:
    AnimationVectorTextureFlyweight* flyweight;
    float textureTime = 0.20f;
    float elapsedTime = 0;
    int currentTexture = 0;
    int startID = 0;
    int endID = 0;
public:
    AnimationVectorTexture(std::string name);
    void draw(float posX, float posY, float rotation = 0.f);
    void update();
    void setTextureRange(int start, int end);
};