#include"../../assets/images/Coordinate.h"

class Animation {
protected:
    vector<Rectangle> frames;
    int currentFrame;
    Texture2D sprite;
    float frameTime;
public:
    Animation();
    Animation(const vector<Rectangle>& frames, const Texture2D& sprite, float frameTime = 0.2f);
    void setFrames(const vector<Rectangle>& newFrames);
    void update(float deltaTime = GetFrameTime(), int startFrame = 0, int size = -1);
    void draw(Vector2 position, float scale = 1.0f) const;
    void reset();
};