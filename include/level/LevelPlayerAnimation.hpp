#pragma once
#include<entities/Character.hpp>

class SubLevelAnimation {
    public:
        virtual bool isDone() = 0;
        virtual void update() = 0;
};

class PlayerDownPipeAnimation : public SubLevelAnimation {
    private:
        float targetY;
        Character* player;
    public:
        PlayerDownPipeAnimation(Character* player);
        bool isDone() override;
        void update() override;
};

class PlayerIntoLeftPipeAnimation : public SubLevelAnimation {
    private:
        float targetX;
        Character* player;
    public:
        PlayerIntoLeftPipeAnimation(Character* player);
        bool isDone() override;
        void update() override;
};

class PlayerIntoRightPipeAnimation : public SubLevelAnimation {
    private:
        float targetX;
        Character* player;
    public:
        PlayerIntoRightPipeAnimation(Character* player);
        bool isDone() override;
        void update() override;
};

class PlayerUpPipeAnimation : public SubLevelAnimation {
    private:
        float targetY;
        Character* player;
    public:
        PlayerUpPipeAnimation(Character* player);
        bool isDone() override;
        void update() override;
};