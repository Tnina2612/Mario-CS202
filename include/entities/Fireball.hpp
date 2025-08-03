#include "raylib.h"
#include <vector>
#include "Coordinate.h"
class Fireball {
public:
    Vector2 position;
    Vector2 velocity;
    bool active;

    Fireball(Vector2 pos, Vector2 vel)
        : position(pos), velocity(vel), active(true) {}

    void Update(float dt) {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        // Thêm kiểm tra va chạm hoặc ra khỏi màn hình
    }

    void Draw() {
        // Sử dụng frame Firebar
        DrawTextureRec(
            fireballTexture, 
            EnemySprite::Fireball::Frames.at("Normal")[0], 
            position, 
            WHITE
        );
    }
};