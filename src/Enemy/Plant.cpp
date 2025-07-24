#include<vector>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Plant.hpp"


Plant::Plant() : Enemy() {
}

Plant::Plant(const std::string& name) : Enemy(name) {
    Rectangle hitbox = {0,0,1,1};
    m_data = EnemyData ( hitbox, 10, false, false, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    
}

Plant::Plant(const std::string& name, Vector2 pos)
    : Plant(name) {
        m_data._pos = pos;
}

// void Plant::update(float dt) {
//     if(!m_data._isActive || !isAlive()) {
//         return;
//     }

//     if(this->isAlive()) {
//         Enemy::update(dt);
//     }
    
//     // else {

//     // }
// }

// void Plant::draw() {
//     if(!m_data._isActive || !isAlive()) {
//         return;
//     }
//     Enemy::draw();
// }