#include<cmath>
#include<random>
#include<algorithm>
#include<iostream>

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
    m_data = EnemyData (width, height, 10, false, true, true, false, 4, 
                        Vector2{10,0}, Vector2{0,0}, -1);

    m_data._velocity = Vector2{0.f, 0.f};

    m_animation.setSprite(EnemyFactory::getEnemyTypes()->sprite);
    allFrames = EnemySprite::BowserSprite::Frames;
    m_animation.setFrames(allFrames["LIdle"]);

}

Bowser::Bowser(const std::string& name, Vector2 pos, Character* character) 
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

Character* Bowser::getTarget() {
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
    if(isMarioClose() && r % 3 != 1) {
        if(m_target->getPos().y < m_data._pos.y) {
            skills.push_back(std::make_shared<JumpCommand>());
            skills.push_back(std::make_shared<BreathFire>());
        }
        else {
            skills.push_back(std::make_shared<ChaseCommand>());
            skills.push_back(std::make_shared<BreathFire>());
        }
    }
    else if (r < 15) {
        skills.push_back(std::make_shared<JumpCommand>());
    } 
    else if (r < 60) {
        int t = dis(gen);
        if(isMarioClose() || t%4 != 1) {
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

bool Bowser::isAlive() {
    return m_data._hp > 0;
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
    fire->setActive(true);
    fireballs.push_back(fire);
}

void Bowser::draw() {
    if(!m_data._isActive) {
        return;
    }
    if(!_dying) {
        DrawRectangleRec(getHitBoxes()[0], RED);
        m_animation.draw(m_data._pos);
    }
    else {
        defeatDraw();
    }

    if(!isAlive()) {
        return;
    }

    for(const auto& f : fireballs) {
        if(!f->isActive()) continue;
        f->draw();
    }
}

void Bowser::clear() {
    forceFinishedAll();
    fireballs.clear();
}

void Bowser::enterEffect() {
    m_defeatEffect.phase = 1;
    m_defeatEffect.radius = 0.f;
    m_defeatEffect.duration = 0.f;
    m_defeatEffect.rotation = 0.f;
    m_defeatEffect.scale = 1.f;
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
    if(isAlive()) {
        generateCommand(dt);
        processCommand(dt);
        m_animation.update(dt);
        for(const auto& f : fireballs) {
            if(!f->isActive()) continue;
            f->update(dt);
        }

        fireballs.erase(
            std::remove_if(fireballs.begin(), fireballs.end(),
                [](const std::shared_ptr<Fireball>& f) {
                    return !f || !f->isActive();
                }),
            fireballs.end()
        );
    }
    else if(!_dying) {
        _dying = true;
        clear();
        enterEffect();
    }

    if(_dying) {
        defeatUpdate(dt);
    }
}

void Bowser::defeatDraw() {
    if(m_defeatEffect.phase == 1) {
        Vector2 center = { m_data._pos.x + m_data._hitBoxWidth / 2, m_data._pos.y + m_data._hitBoxHeight / 2 };
        DrawCircleGradient(center.x, center.y, m_defeatEffect.radius, BLACK, DARKGRAY);
        m_animation.draw(m_data._pos);
    }
    else if(m_defeatEffect.phase == 2) {
        Vector2 center = { m_data._pos.x + m_data._hitBoxWidth / 2, m_data._pos.y + m_data._hitBoxHeight / 2 };
        DrawCircleGradient(center.x, center.y, m_defeatEffect.radius, BLACK, DARKGRAY);
        for (int i = 0; i < 4; i++) {
            float r = std::max((float) (m_defeatEffect.radius - 30.f + i * 10 + sin(GetTime() * 4) * 2), 0.f);
            Color c = Fade(BLACK, 0.2f - i*0.05f);
            DrawCircleGradient(center.x, center.y, r, c, DARKGRAY);
        }
        m_animation.drawV2(center, m_defeatEffect.rotation, m_defeatEffect.scale);
    }
}

void Bowser::defeatUpdate(float dt) {
    if(m_defeatEffect.phase == 1) {
        m_defeatEffect.radius = std::min(m_defeatEffect.radius + 40.f*dt, 50.f);
        if(m_defeatEffect.radius == 50.f) {
            m_defeatEffect.duration += dt;
            if(m_defeatEffect.duration >= 1.2f) {
                m_defeatEffect.phase = 2;
                m_defeatEffect.scale = 1.f;
                m_defeatEffect.rotation = 0.f;
                m_defeatEffect.duration = 0.f;
            }
        }

    }
    else if(m_defeatEffect.phase == 2) {
        m_defeatEffect.scale -= 0.5 * dt;
        m_defeatEffect.rotation += 720.f * dt;
        m_defeatEffect.radius = std::min(m_defeatEffect.radius - 25.f * dt, 50.f);

        if(m_defeatEffect.scale <= 0.f) {
            m_defeatEffect.phase = 0;
        }
        if(m_defeatEffect.radius <= 0.f) {
            m_defeatEffect.radius = 0.f;
            m_defeatEffect.phase = 3;
        }
    }

}
