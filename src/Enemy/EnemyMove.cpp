#include"raylib.h"

#include"../../include/entities/Enemy/EnemyMove.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"

//Movement
void DirectionMove::Execute(EnemyData& data, float dt) {
    data._pos.x += data._velocity.x * dt;
    data._pos.y += data._velocity.y * dt;
}

void JumpMove::Execute(EnemyData& data, float dt) {
    data._velocity.y += data._gravity * dt;

    data._pos.x += data._velocity.x * dt;
    data._pos.y += data._velocity.y * dt;

    if(data._isOnGround) {
        //data._pos.y = ;
    }
}

void PatrolMove::Execute(EnemyData& data, float dt) {
    
}