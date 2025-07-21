#include"raylib.h"

#include"../include/entities/Enemy"


//Movement
void DirectionMove::Execute(Enemy& enemy, float dt) {
    Vector2 baseSpeed = enemy.getBaseSpeed();

    enemy._velocity.x = direction.x * baseSpeed.x;
    enemy._velocity.y = direction.y * baseSpeed.y;
}

void JumpMove::Execute(Enemy& enemy, float dt) {
    if(enemy._isOnGround && direction.y < 0) {
        enemy._velocity.y = -500;           //< 
        enemy._isOnGround = false;
    }

    Vector2 baseSpeed = enemy.getBaseSpeed();
    
    enemy._velocity.x = baseSpeed.x;
}