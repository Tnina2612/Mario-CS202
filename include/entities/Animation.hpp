#include"../../assets/images/Coordinate.h"

class Animation {
protected:
    float scale;
    vector<Rectangle> frames;
    int currentFrame;
    Texture2D sprite;
    float frameTime;
    const float defaultFrameTime = 0.2f; // Default frame time if not specified
public:
    Animation();
    Animation(const vector<Rectangle>& frames, const Texture2D& sprite, float frameTime = 0.2f, float scale = 1.0f);
    void setFrames(const vector<Rectangle>& newFrames);
    void update(float deltaTime = GetFrameTime(), int startFrame = 0, int size = -1);
    void draw(Vector2 position) const;
    void reset();
    void setScale(float scale);
};