#pragma once

class Bowser;

class ICommand {
protected:
    bool _isFinished = false;
public:
    virtual ~ICommand() = default;
    virtual bool isFinished();
    virtual void execute(Bowser& bowser) = 0;               //< set frame and state, set up for action
    virtual void update(Bowser& bowser, float dt) = 0;
};

class JumpCommand : public ICommand {
private:
    int dir;
    Vector2 startPos;
    Vector2 velocity;
    float gravityUp = 100.f;
    float gravityDown = 150.f;
    bool isFalling;
    int phase;                      //1: jump forward, -1 move backward
public:
    void execute(Bowser& bowser) override;
    void update(Bowser& bowser, float dt) override;
};  

class BreathFire : public ICommand {
private:
    int curFrame;
public:
    void execute(Bowser& bowser) override;
    void update(Bowser& bowser, float dt) override;
};  

class ChaseCommand : public ICommand {
private:
    int phase;          //1: forward, -1 backward
    float range;
    Vector2 velocity;
    Vector2 startPos;
public:
    void execute(Bowser& bowser) override;
    void update(Bowser& bowser, float dt) override;
};  

// class ComboCommand : public ICommand {

// }