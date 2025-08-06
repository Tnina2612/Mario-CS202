#include<cmath>
#include<random>

#include"../../include/entities/Enemy/Bowser.hpp"
#include"../../include/entities/Enemy/BossCommand.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());


bool ICommand::isFinished() {
    return _isFinished;
}

void JumpCommand::execute(Bowser& bowser) {
    startPos = bowser.getPos();

    std::uniform_int_distribution<> dis(1, 7);
    int r = dis(gen);

    isFalling = false;
    phase = 1;
    dir = bowser.getDir();
    velocity = Vector2{0.f + (r%4 != 0)*40.f* dir , -100.f};
}

void JumpCommand::update(Bowser& bowser, float dt) {
    Vector2 pos = bowser.getPos();

    if (velocity.y > 0 && phase == 1) {
        isFalling = true;
        velocity.y += gravityDown * dt;
    } 
    else if(phase == 1){
        velocity.y += gravityUp * dt;
    }

    pos.y += velocity.y * dt;
    pos.x += velocity.x * dt;

    float dx = pos.x - startPos.x;
    float dy = pos.y - startPos.y;

    if(isFalling && pos.y >= startPos.y) {
        if(phase == 1) {
            pos.y = startPos.y;
            velocity = Vector2{50.f * bowser.getDir() *-1 , 0.f};
            phase = -1;
        }
    }
    if(dx*dx + dy*dy < 4.f && phase == -1) {
        bowser.setPosition(startPos);
        _isFinished = true;
    }

    bowser.setPosition(pos);
}

void BreathFire::execute(Bowser& bowser) {
    curFrame = 0;
    if(bowser.getDir() == 1)
        bowser.setAniFrames(bowser.getFrames("RBreath"));
    else 
        bowser.setAniFrames(bowser.getFrames("LBreath"));
}

void BreathFire::update(Bowser& bowser, float dt) {
    curFrame++;

    if (curFrame == 10) {
        bowser.spawnFireball();
    }

    if (curFrame >= 30) {
        int dir = bowser.getDir();
        if(dir == 1) {
            bowser.setAniFrames(bowser.getFrames("RIdle"));
        }
        else if(dir == -1) {
            bowser.setAniFrames(bowser.getFrames("LIdle"));
        }
        _isFinished = true;
    }
}

void ChaseCommand::execute(Bowser& bowser) {
    phase = 1;
    startPos = bowser.getPos();

    int dir = bowser.getDir();

    std::uniform_int_distribution<> dis(0, 99);
    int r = dis(gen);
    //bowser may go off-screen
    range = 100.f + (r%3+1)*20;     

    velocity = Vector2{125.f*dir, 0.f};
    
    if(dir == 1) {
        bowser.setAniFrames(bowser.getFrames("RBreath"));
    }
    else if(dir == -1) {
        bowser.setAniFrames(bowser.getFrames("LBreath"));
    }
}

void ChaseCommand::update(Bowser& bowser, float dt) {
    Vector2 pos = bowser.getPos();
    
    float dx = velocity.x * dt;
    float dy = velocity.y * dt;
    
    pos.x += dx;
    pos.y += dy;

    range -= sqrt(dx*dx + dy*dy);
    if(phase == -1) {
        Vector2 targetPos = bowser.getTarget()->getPos();

        float dx1 = pos.x - targetPos.x;
        float dy1 = pos.y - targetPos.y;

        if (sqrt(dx1 * dx1 + dy1 * dy1) < 28.f) {
            _isFinished = true;
            return;
        } 
    }

    if(range <= 0) {
        if(phase == 1) {
            phase = -1;
            Vector2 pos1 = bowser.getPos();
            float dx1 = pos1.x - startPos.x;
            float dy1 = pos1.y - startPos.y;
            range = sqrt(dx1*dx1 + dy1*dy1);
            velocity.x *= -0.8f;

            if (velocity.x > 0) {
                bowser.setAniFrames(bowser.getFrames("RIdle"));
            } 
            else {
                bowser.setAniFrames(bowser.getFrames("LIdle"));
            }
            
        }
        else {
            _isFinished = true;
        }
            
    }

    bowser.setPosition(pos);
}