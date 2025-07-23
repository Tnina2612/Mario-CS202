#include"raylib.h"

#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/entities/Enemy/Enemy.hpp"


//Movement
void DirectionMove::Execute(Enemy& enemy, float dt) {
    Vector2 baseSpeed = enemy.getBaseSpeed();

    float vx = direction.x * baseSpeed.x;
    float vy = direction.y * baseSpeed.y;

    enemy.setVelocity(Vector2{vx, vy});
}

void JumpMove::Execute(Enemy& enemy, float dt) {
    // if(enemy._isOnGround && direction.y < 0) {
    //     enemy._velocity.y = -500;           //< 
    //     enemy._isOnGround = false;
    // }

    // Vector2 baseSpeed = enemy.getBaseSpeed();
    
    // enemy._velocity.x = baseSpeed.x;
}