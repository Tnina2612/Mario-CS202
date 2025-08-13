// // MovingPlatform.h
// #pragma once
// #include "GameObject.h"
// #include "raylib.h"

// enum class MoveDirection { Horizontal, Vertical };
// enum class PlatformSize { Small, Medium, Large };

// class MovingPlatform{
// private:
//     Vector2 startPos;  
//     float distance;      
//     float speed;      
//     MoveDirection direction;
//     float timeCounter;    
// public:
//     PlatformSize size;     

//     MovingPlatform(Vector2 pos, float dist, float spd, MoveDirection dir, Texture2D tex, PlatformSize s);

//     void Update(float deltaTime) override;
//     void Draw() override;
//     Rectangle getRect() const; 
// };
