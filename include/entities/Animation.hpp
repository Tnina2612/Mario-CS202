#pragma once
#include"../../assets/images/Coordinate.h"
#include<entities/AnimationVectorTextureFlyweight.hpp>
#include<core/Variables.hpp>

class Animation {
protected:
    float scale;
    vector<Rectangle> frames;
    int currentFrame;
    
    float frameTime;
    const float defaultFrameTime = 0.1f; // Default frame time if not specified
    Texture2D sprite;
public:
    Animation();
    Animation(const vector<Rectangle>& frames);
    Animation(const vector<Rectangle>& frames, const Texture2D& sprite, float frameTime = 0.2f, float scale = 1.0f);
    void setFrames(const vector<Rectangle>& newFrames);
    void update(float deltaTime, int startFrame = 0, int size = -1);
    void draw(Vector2 position) const;
    void reset();
    void setScale(float scale);
    float getScale() const;
    void setSprite(const Texture2D& sprite);
    virtual ~Animation() = default;
};

class AnimationVectorTexture {
private:
    AnimationVectorTextureFlyweight* flyweight;
    float textureTime = 0.5f;
    float elaspedTime = 0;
    int currentTexture = 0;
    int startID = 0;
    int endID = 0;
public:
    AnimationVectorTexture(std::string name);
    void draw(float posX, float posY);
    void update();
    void setTextureRange(int start, int end);
};