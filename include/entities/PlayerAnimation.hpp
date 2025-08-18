#pragma once
#include<entities/Character.hpp>
#include<level/TileMap.hpp>

class PlayerAnimation {
    public:
        virtual void initialize(Character* player) = 0;
        virtual bool isDone() = 0;
        virtual void update() = 0;
        virtual string getType() const = 0;
        virtual void saveToFile(std::ofstream& out) const = 0;
        virtual ~PlayerAnimation() = default;
};

class PlayerDownPipeAnimation : public PlayerAnimation {
    private:
        float targetY;
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerIntoLeftPipeAnimation : public PlayerAnimation {
    private:
        float targetX;
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerIntoRightPipeAnimation : public PlayerAnimation {
    private:
        float targetX;
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerUpPipeAnimation : public PlayerAnimation {
    private:
        float targetY;
        Character* player;
    public:
        PlayerUpPipeAnimation(float targetY);
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerClimbDownFlagColumnAnimation : public PlayerAnimation {
    private:
        const float pivotX;
        const float targetY;
        const bool directionAfterClimbIsRight;
        const float waitTime = 0.5f;
        Character* player;
        float elapsedTime;
        bool music = false;
    public:
        PlayerClimbDownFlagColumnAnimation(float pivotX, float targetY, bool directionAfterClimbIsRight);
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerWalkToXAnimation : public PlayerAnimation {
    private:
        float targetX;
        Character* player;
        TileMap* blocks;
    public:
        PlayerWalkToXAnimation(float targetX, TileMap* blocks);
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerEnterDoorAnimation : public PlayerAnimation {
    private:
        float targetTime;
        float elapsedTime;
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerExitDoorAnimation : public PlayerAnimation {
    private:
        float targetTime;
        float elapsedTime;
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerGrowAnimation : public PlayerAnimation {
    private:
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerShrinkAnimation : public PlayerAnimation {
    private:
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerWaitAnimation : public PlayerAnimation {
    private:
        const float waitTime;
        float elapsedTime = 0.f;
        Character * player;
    public:
        PlayerWaitAnimation(float waitTime = 0.5f);
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerWinAnimation : public PlayerAnimation {
    private:
        Character * player;
        bool printText1 = false;
        bool printText2 = false;
        const float waitTime;
        float elapsedTime = 0.f;
    public:
        PlayerWinAnimation();
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};