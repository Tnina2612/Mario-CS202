#include<vector>

#include"../../include/entities/Enemy/EnemyType.hpp"
#include"../../include/entities/Enemy/EnemyData.hpp"
#include"../../include/entities/Enemy/Plant.hpp"
#include"../../include/entities/Enemy/EnemyMove.hpp"

#include<iostream>

Plant::Plant() : Enemy() {
    m_data._velocity = Vector2{0,-50.f};
    _curHeight = m_data._pos.y;
    _curCD = 0.f;
    _inCD = false;
    _curDir = -1;
    _maxHeight = 100.f;
}

Plant::Plant(const std::string& name) : Enemy(name) {
    float width = 16.f;
    float height = 16.f;
    m_data = EnemyData (width, height, 10, false, false, true, 1, 
                        Vector2{10,0}, Vector2{0,0}, -1);
    m_data._velocity = Vector2{0,-50.f};
    _curHeight = m_data._pos.y;
    _curCD = 0.f;
    _inCD = false;    
    _curDir = -1;
    _maxHeight = 100.f;
}

Plant::Plant(const std::string& name, Vector2 pos)
    : Plant(name) {
        m_data._pos = pos;
}

void Plant::update(float dt) {
    if(!m_data._isActive) {
        return;
    }

    if(_inCD) {
        _curCD += dt;
        if(_curCD > _cdTime) {
            _inCD = false;
            _curCD = 0;
        }
        return;
    }

    _curHeight += abs(m_data._velocity.y) * dt * -1 * _curDir;
    if(_curHeight < 0) {
        _curHeight = 0;
        _curDir = -1;
        _inCD = true;
        _cdTime = 1.f;
    }
    else if(_curHeight > _maxHeight){
        _curHeight = _maxHeight;
        _curDir = 1;
        _inCD = true;
        _cdTime = 0.05f;
    }

    if(m_data._dir != _curDir) {
        m_data._dir = _curDir;
        Vector2 d = {0.f, m_data._velocity.y*-1.f};
        m_data._velocity = d;
        setMovementStrategy(std::make_shared<DirectionMove>());
    }

    Enemy::update(dt);
}

void Plant::onEnemyCollision(Enemy& enemy) {
    return; // Plant does not interact with other enemies
}