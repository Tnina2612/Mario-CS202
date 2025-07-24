#include"raylib.h"

#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/entities/Enemy/Enemy.hpp"

#include<iostream>

//Movement
void DirectionMove::Execute(Vector2& position, float dt) {
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
}

void JumpMove::Execute(Vector2& position, float dt) {
    velocity.y += gravity * dt;

    position.y += velocity.y * dt;
    position.x += velocity.x * dt;

    if (position.y >= 50.0f) { //ground level = 500
        position.y = 50.0f;
        velocity.y = -jumpHeight;
    }
}