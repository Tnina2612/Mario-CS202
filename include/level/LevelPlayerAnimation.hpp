#pragma once
#include<entities/Character.hpp>
#include<level/TileMap.hpp>

class SubLevelAnimation {
    public:
        virtual void initialize(Character* player) = 0;
        virtual bool isDone() = 0;
        virtual void update() = 0;
        virtual string getType() const = 0;
        virtual void saveToFile(std::ofstream& out) const = 0;
        virtual ~SubLevelAnimation() = default;
};

class PlayerDownPipeAnimation : public SubLevelAnimation {
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

class PlayerIntoLeftPipeAnimation : public SubLevelAnimation {
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

class PlayerIntoRightPipeAnimation : public SubLevelAnimation {
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

class PlayerUpPipeAnimation : public SubLevelAnimation {
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

class PlayerClimbDownAnimation : public SubLevelAnimation {
    private:
        float pivotX;
        float targetY;
        Character* player;
    public:
        PlayerClimbDownAnimation(float pivotX, float targetY);
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerWalkToXAnimation : public SubLevelAnimation {
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

class PlayerEnterDoorAnimation : public SubLevelAnimation {
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

class PlayerExitDoorAnimation : public SubLevelAnimation {
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

class PlayerGrowAnimation : public SubLevelAnimation {
    private:
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};

class PlayerShrinkAnimation : public SubLevelAnimation {
    private:
        Character* player;
    public:
        void initialize(Character* player) override;
        bool isDone() override;
        void update() override;
        string getType() const override;
        void saveToFile(std::ofstream& out) const override;
};