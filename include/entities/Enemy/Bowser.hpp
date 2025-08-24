#pragma once

#include<memory>
#include<queue>
#include<deque>

#include"EnemyData.hpp"
#include"Fireball.hpp"
#include<entities/Animation.hpp>
#include<entities/Character.hpp>

class ICommand;
class EnemyManager;

struct DefeatEffect {
    int phase = 0;
    float radius = 0.f;
    float duration = 0.f;
    float rotation = 0.f;
    float scale = 1.f;
};

class Bowser //: public Enemy {
{
friend class EnemyManager;
private:
    DefeatEffect m_defeatEffect;
    Animation m_animation;
    EnemyData m_data;
    std::unordered_map<std::string, std::vector<Rectangle>> allFrames;
    std::queue<std::shared_ptr<ICommand>> _commandsQueue;
    std::shared_ptr<ICommand> _curCommand   = nullptr;
    Character* m_target   = nullptr;

    std::vector<shared_ptr<Fireball>> fireballs;

    bool _isFree    = true;
    bool _dying     = false;

    const float _processCommandTimeGap  = 4.f;
    const float _TIME                   = 30.f;
    float _time                         = 0.f;
    float _elapsedTime                  = 0.f;
    
    int _deadScene;                         //< 0: not yet, 1: hp=0, 2: bridge, 3: survive
    void processCommand(float dt);          // 
    void generateCommand(float dt);         //
    std::vector<std::shared_ptr<ICommand>> generateSkill();           //< generate combo 
    void forceFinished();                   //< force finished current command
    void forceFinishedAll();                //< finised all commands in _commandsQueue
    bool isMarioClose(float distance = 50.0f);
    // void fall();                         //< bridge destruction
    void check();                           //< check if bowser is defeated
    bool isAlive();
    void clear();
    void enterEffect();
    void defeatDraw();
    void defeatUpdate(float dt);
public:
    Bowser();
    Bowser(const std::string& name);
    Bowser(const std::string& name, Vector2 pos, Character* character);

    void connectToPlayer(Character* character);

    // void respawn();
    bool beHitByFireball();

    std::vector<Rectangle> getHitBoxes();       //< hit-boxes of bowser and fireballs
    Vector2 getVelocity();
    int getDir();
    std::vector<Rectangle> getFrames(const std::string& name);
    Vector2 getPos();
    Character* getTarget();

    void setActive(bool isActive);
    void setPosition(Vector2 pos);
    void setAniFrames(std::vector<Rectangle> frames);

    void spawnFireball();

    void update(float dt = GetFrameTime());                      //< update: Bowser and fireballs
    void draw();                                //< draw Bowser and fireballs
};