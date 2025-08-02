#include<cmath>
#include<random>

#include"../../include/entities/Enemy/EnemyFactory.hpp"
#include"../../include/entities/Enemy/Bowser.hpp"
#include"../../include/entities/Enemy/BossCommand.hpp"
#include"../../assets/images/Coordinate.h"

static std::random_device rd;
static std::mt19937 gen(rd());

Bowser::Bowser() {}

Bowser::Bowser(const std::string& name) {
    _dying = false;
    _isFree = true;

    float width = 20.f;
    float height = 20.f;
    m_data = EnemyData (width, height, 10, false, true, true, 3, 
                        Vector2{10,0}, Vector2{0,0}, -1);

    m_data._velocity = Vector2{0.f, 0.f};

    m_animation.sprite = EnemyFactory::getEnemyTypes()->sprite;
    allFrames = EnemySprite::Bowser::Frames;
    m_animation.setFrames(allFrames["LIdle"]);

}

Bowser::Bowser(const std::string& name, Vector2 pos, std::shared_ptr<Character> character) 
    : Bowser(name)
{  
    m_data._pos = pos;
    m_target = character;
}

void Bowser::check() {
    if(m_data._hp <= 0) {
        m_animation.setFrames(allFrames["LIdle"]);
        _dying = true;
        _deadScene = 1;
        return;
    }
    else if(_elapsedTime > _TIME) {
        // survive _TIME -> win
        _dying = true;
        _deadScene = 3;
    }
    // else if() {
    //     _dying = true;
    //     _deadScene = 2;
    // }

}
bool Bowser::isMarioClose(float distance) {
    Vector2 pos = m_target->getPos();
    float dis = pow(m_data._pos.x - pos.x, 2) + pow(m_data._pos.y - pos.y, 2);
    return sqrt(dis) < distance;
}

void Bowser::processCommand(float dt) {
    // cooldown
    if(_isFree) {
        _time += dt;
    }
    if(!_curCommand) {
        return;
    }
    //Execute command
    if(_isFree && _time > _processCommandTimeGap) {
        _curCommand->execute(*this);
        _isFree = false;
        _time = 0.f;
    }

    _curCommand->update(*this, dt);
    if(_curCommand->isFinished()) {
        _isFree = true;
        _curCommand = nullptr;
        _state = State::Idle;
    }

}

void Bowser::generateCommand(float dt) {
    if(_curCommand) {
        return;
    }
    _time += dt;
    if(_time < _processCommandTimeGap) {
        return;
    }
    auto skills = generateSkill();
    for(int i = 0; i < skills.size(); i++) {
        _commandsQueue.push(skills[i]);
    }

    if(!_commandsQueue.empty()) {
        _curCommand = _commandsQueue.front();
        _commandsQueue.pop();
    }
    _time = 0.f;
}

std::vector<std::shared_ptr<ICommand>> Bowser::generateSkill() {
    std::vector<std::shared_ptr<ICommand>> skills;

    std::uniform_int_distribution<> dis(0, 99);
    int r = dis(gen);


    if (r < 15) {
        skills.push_back(std::make_shared<JumpCommand>());
    } 
    else if (r < 60) {
        int t = dis(gen);
        if(isMarioClose() || t%7 == 1) {
            skills.push_back(std::make_shared<ChaseCommand>());
        }
        else {
            skills.push_back(std::make_shared<BreathFire>());
        }
    } 
    else if (r < 80) {
        skills.push_back(std::make_shared<JumpCommand>());
        skills.push_back(std::make_shared<BreathFire>());
    } 
    else {
        skills.push_back(std::make_shared<ChaseCommand>());
        skills.push_back(std::make_shared<BreathFire>());
    }
    return skills;
}

void Bowser::forceFinished() {
    if (_curCommand) {
        _curCommand = nullptr;
        _isFree = true;
        _state = State::Idle;
    }
}

void Bowser::forceFinishedAll() {
    forceFinished();
    while(!_commandsQueue.empty()) _commandsQueue.pop();
}

bool Bowser::beHitByFireball() {
    if(!m_data._isActive) {
        return false;
    }
    m_data._hp --;
    return true;
}

std::vector<Rectangle> Bowser::getHitBoxes() {
    std::vector<Rectangle> res;
    
    res.push_back(Rectangle{m_data._pos.x, m_data._pos.y, m_data._hitBoxWidth, m_data._hitBoxHeight});
    for(const auto& x : fireballs) {
        res.push_back(x->getHitBox());
    }
    return res;
}

void Bowser::spawnFireball() {
    Vector2 startPos = Vector2{m_data._pos.x - 5 * m_data._dir, m_data._pos.y + 4};
    Vector2 pos = Vector2{m_data._pos.x - 20 * m_data._dir, m_target->getPos().y};
    std::shared_ptr<Fireball> fire = std::make_shared<Fireball>(startPos, pos);
    fireballs.push_back(fire);
}

void Bowser::draw() {
    if(!m_data._isActive) {
        return;
    }
    m_animation.draw(m_data._pos);
    for(const auto& f : fireballs) {
        f->draw();
    }
}
void Bowser::update(float dt) {
    if(!m_data._isActive) {
        return;
    }

    _elapsedTime += dt;

    //check();

    // if(_dying) {
    //     //not update animation -> set currentFrame = 0;
    //     // m_animation.setFrames(allFrames["LIdle"]);   //< force
    //     // dead scene
    // }
    // else {
        m_animation.update(dt);
        for(const auto& f : fireballs) {
            f->update(dt);
        }

        //processCommand(dt);
    //}
}


