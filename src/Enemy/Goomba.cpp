#include<vector>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Goomba.hpp"


Goomba::Goomba() : Enemy() {
}

Goomba::Goomba(const std::string& name) : Enemy(name) {
    Rectangle hitbox = {0,0,1,1};
    m_data = EnemyData ( hitbox, 10, false, true, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    
}

Goomba::Goomba(const std::string& name, Vector2 pos)
    : Goomba(name) {
        m_data._pos = pos;
}

// void Goomba::update(float dt) {
//     if(!m_data._isActive || !isAlive()) {
//         return;
//     }

//     if(this->isAlive()) {
//         Enemy::update(dt);
//     }
    
//     // else {

//     // }
// }

// void Goomba::draw() {
//     if(!m_data._isActive || !isAlive()) {
//         return;
//     }
//     Enemy::draw();
// }