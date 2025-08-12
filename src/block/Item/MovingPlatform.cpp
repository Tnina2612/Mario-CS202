// // MovingPlatform.cpp
// #include "MovingPlatform.h"
// #include <cmath>

// MovingPlatform::MovingPlatform(Vector2 pos, float dist, float spd, MoveDirection dir, Texture2D tex, PlatformSize s)
//     : GameObject(tex, pos), startPos(pos), distance(dist), speed(spd), direction(dir), timeCounter(0.0f), size(s) {}

// void MovingPlatform::Update(float deltaTime) {
//     timeCounter += speed * deltaTime; // Tăng góc theo thời gian

//     if (direction == MoveDirection::Horizontal) {
//         position.x = startPos.x + sinf(timeCounter) * distance;
//     }
//     else {
//         position.y = startPos.y + sinf(timeCounter) * distance;
//     }
// }

// void MovingPlatform::Draw() {
//     DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
// }

// Rectangle MovingPlatform::getRect() const {
//     return { position.x, position.y, (float)texture.width, (float)texture.height };
// }
