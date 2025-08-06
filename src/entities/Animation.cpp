#include "../include/entities/Animation.hpp"
#include "core/Variables.hpp"
#include <iostream>

Animation::Animation() : currentFrame(0), frameTime(0.0f), scale(1) {}

Animation::Animation(const vector<Rectangle>& frames) : Animation() {
    this->frames = frames;
}

Animation::Animation(const vector<Rectangle>& frames, const Texture2D& sprite, float frameTime, float scale)
    : frames(frames), currentFrame(0), sprite(sprite), frameTime(frameTime), scale(scale) {}

void Animation::setFrames(const vector<Rectangle>& newFrames) {
    frames = newFrames;
    currentFrame = 0; // Reset to the first frame
}

void Animation::update(float deltaTime, int startFrame, int size) {
    if(frames.empty()) return;
    if (size <= -1 || size > frames.size()) {
        size = frames.size();
    }
    if (startFrame < 0 || startFrame >= frames.size()) {
        startFrame = 0; // Ensure startFrame is within bounds
    }
    frameTime -= deltaTime;
    if(frameTime <= 0.0f) {
        currentFrame++;
        if(currentFrame >= startFrame + size || currentFrame < startFrame) {
            currentFrame = startFrame; // Loop back to the start frame
        }
        frameTime = defaultFrameTime; // Reset frame time
    }
}

void Animation::draw(Vector2 position) const {
    if(frames.empty()) return;
    Rectangle sourceRect = frames[currentFrame];
    DrawTexturePro(sprite, sourceRect, {position.x, position.y, sourceRect.width * scale, sourceRect.height * scale}, {0, 0}, 0.0f, WHITE);
}

void Animation::reset() {
    currentFrame = 0; // Reset to the first frame
    frameTime = defaultFrameTime; // Reset frame time
}

void Animation::setScale(float scale) {
    this->scale = scale;
}

float Animation::getScale() const {
    return scale;
}