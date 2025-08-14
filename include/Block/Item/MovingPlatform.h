// // MovingPlatform.h
// #pragma once
// #include "GameObject.h"
// #include "raylib.h"

// enum class MoveDirection { Horizontal, Vertical };
// enum class PlatformSize { Small, Medium, Large };

// class MovingPlatform : public GameObject {
// private:
//     Vector2 startPos;      // Vị trí ban đầu
//     float distance;        // Biên độ di chuyển
//     float speed;           // Tốc độ dao động
//     MoveDirection direction;
//     float timeCounter;     // Đếm thời gian cho sin/cos
// public:
//     PlatformSize size;     // Kích thước platform

//     MovingPlatform(Vector2 pos, float dist, float spd, MoveDirection dir, Texture2D tex, PlatformSize s);

//     void Update(float deltaTime) override;
//     void Draw() override;
//     Rectangle getRect() const; // Lấy hình chữ nhật va chạm
// };
