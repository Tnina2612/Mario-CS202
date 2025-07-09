#include"../include/entities/Animation.hpp"

Animation::Animation() : currentFrame(0), frameTime(0.2f) {}
Animation::Animation(const vector<Rectangle>& frames, const Texture2D& sprite, float frameTime)
    : frames(frames), currentFrame(0), sprite(sprite), frameTime(frameTime) {}

void Animation::setFrames(const vector<Rectangle>& newFrames) {
    frames = newFrames;
    currentFrame = 0; // Reset to the first frame
}

void Animation::update(float deltaTime, int startFrame, int size) {
    if(frames.empty()) return;
    
}