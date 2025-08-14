#include<cmath>
#include<random>

#include"../../include/entities/Enemy/EnemyFactory.hpp"
#include"../../include/entities/Enemy/Bowser.hpp"
#include"../../include/entities/Enemy/BossCommand.hpp"
#include"../../assets/images/Coordinate.h"
#include"../../include/core/Variables.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());

Bowser::Bowser() {}

Bowser::Bowser(const std::string& name) {
    _dying = false;
    _isFree = true;

    float width = 35.f;
    float height = 35.f;
    m_data = EnemyData (width, height, 10, false, true, true, false, 3, 
                        Vector2{10,0}, Vector2{0,0}, -1);

    m_data._velocity = Vector2{0.f, 0.f};

    m_animation.setSprite(EnemyFactory::getEnemyTypes()->sprite);
    allFrames = EnemySprite::Bowser::Frames;
    m_animation.setFrames(allFrames["LIdle"]);

}

Bowser::Bowser(const std::string& name, Vector2 pos, std::shared_ptr<Character> character) 
    : Bowser(name)
{  
    m_data._pos = pos;
    m_target = character;
}

Vector2 Bowser::getVelocity() {
    return m_data._velocity;
}

Vector2 Bowser::getPos() {
    return m_data._pos;
}

void Bowser::setPosition(Vector2 pos) {
    m_data._pos = pos;
}

void Bowser::setActive(bool isActive) {
    m_data._isActive = isActive;
}

std::vector<Rectangle> Bowser::getFrames(const std::string& name) {
    if(allFrames.find(name) != allFrames.end()) {
        return allFrames[name];
    }
    return {};
}

void Bowser::setAniFrames(std::vector<Rectangle> frames) {
    m_animation.setFrames(frames);
}

int Bowser::getDir() {
    return m_data._dir;
}

std::shared_ptr<Character> Bowser::getTarget() {
    return m_target;
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
    if(!m_target) {
        return false;
    }
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
        if(_commandsQueue.empty()) {
            return;
        }
        _curCommand = _commandsQueue.front();
        _commandsQueue.pop();
    }

    //Execute command
    if(_isFree) {
        _curCommand->execute(*this);
        _isFree = false;
        _time = 0.f;
    }

    _curCommand->update(*this, dt);
    if(_curCommand->isFinished()) {
        _isFree = true;
        _curCommand = nullptr;
        if(m_data._pos.x < m_target->getPos().x) {
            m_data._dir = 1;
            m_animation.setFrames(allFrames["RIdle"]);
        } 
        else if(m_data._pos.x > m_target->getPos().x) {
            m_data._dir = -1;
            m_animation.setFrames(allFrames["LIdle"]);
        }
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
        std::cerr << "Bowser Jump\n";
    } 
    else if (r < 60) {
        int t = dis(gen);
        if(isMarioClose() || t%4 != 1) {
            skills.push_back(std::make_shared<ChaseCommand>());
            std::cerr << "Bowser Chase\n";
        }
        else {
            skills.push_back(std::make_shared<BreathFire>());
            std::cerr << "Bowser Breath\n";
        }
    } 
    else if (r < 80) {
        skills.push_back(std::make_shared<JumpCommand>());
        skills.push_back(std::make_shared<BreathFire>());
        std::cerr << "Bowser Jump + Breath\n";
    } 
    else {
        skills.push_back(std::make_shared<ChaseCommand>());
        skills.push_back(std::make_shared<BreathFire>());
        std::cerr << "Bowser Chase + Breath\n";
    }
    return skills;
}

void Bowser::forceFinished() {
    if (_curCommand) {
        _curCommand = nullptr;
        _isFree = true;
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
    Vector2 startPos = Vector2{m_data._pos.x + 5 * m_data._dir, m_data._pos.y};
    Vector2 pos = Vector2{m_data._pos.x + 10 * m_data._dir, m_target->getPos().y};

    std::shared_ptr<Fireball> fire = std::make_shared<Fireball>(startPos, pos);
    fireballs.push_back(fire);
}

void Bowser::draw() {
    if(!m_data._isActive) {
        return;
    }
    DrawRectangleRec(getHitBoxes()[0], RED);
    m_animation.draw(m_data._pos);

    for(const auto& f : fireballs) {
        DrawRectangleRec(f->getHitBox(), RED);
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

        generateCommand(dt);
        processCommand(dt);
        m_animation.update(dt);
        for(const auto& f : fireballs) {
            f->update(dt);
        }

        //processCommand(dt);
    //}
}


