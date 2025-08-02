#pragma once

#include<memory>
#include<queue>

#include"EnemyData.hpp"
#include"Fireball.hpp"
#include"../../include/entities/Animation.hpp"
#include"../../include/entities/Character.hpp"

class ICommand;

class Bowser //: public Enemy {
{
private:
    Animation m_animation;
    EnemyData m_data;
    std::unordered_map<std::string, std::vector<Rectangle>> allFrames;
    std::queue<std::shared_ptr<ICommand>> _commandsQueue;
    std::shared_ptr<ICommand> _curCommand   = nullptr;
    std::shared_ptr<Character> m_target   = nullptr;
    enum State {
        Idle,
        Jump,
        Breath,
        Chase,
        Die
    } _state;

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
    bool isMarioClose(float distance = 100.0f);
    // void fall();                         //< bridge destruction
    void check();                           //< check if bowser is defeated
public:
    Bowser();
    Bowser(const std::string& name);
    Bowser(const std::string& name, Vector2 pos, std::shared_ptr<Character> character);

    // void respawn();
    bool beHitByFireball();
    std::vector<Rectangle> getHitBoxes();       //< hit-boxes of bowser and fireballs
    
    void spawnFireball();

    void update(float dt);                      //< update: Bowser and fireballs
    void draw();                                //< draw Bowser and fireballs
};