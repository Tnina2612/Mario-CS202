#include"raylib.h"

#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/entities/Enemy/Enemy.hpp"


//Movement
void DirectionMove::Execute(Vector2& position, float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void JumpMove::Execute(Vector2& position, float dt) {
    velocityY += gravity * dt;
        position.y += velocityY * dt;

    if (position.y >= 500.0f) { //ground level = 500
        position.y = 500.0f;
        velocityY = -jumpHeight;
    }
}