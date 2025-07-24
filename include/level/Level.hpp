#pragma once
#include<level/TileMap.hpp>
#include<raylib.h>
#include<iostream>
#include<entities/Character.hpp>
#include<entities/Mario.hpp>
#include<entities/Enemy/Enemy.hpp>
#include<entities/Enemy/EnemyFactory.hpp>

class Level {
    public:
        virtual void draw(void) = 0;
        virtual void update(void) = 0;
        virtual float getWidth(void) = 0;
        virtual float getHeight(void) = 0;
        virtual std::shared_ptr<Character> getCharacter() = 0;
        virtual ~Level() = default;
};

class Level_1_1_Ground : public Level {
        const static int BLOCKSIDE = 16;
        TileMap background;
        TileMap blocks;
        std::shared_ptr<Character> player;
        std::vector<std::shared_ptr<Enemy>> enemies;
    public:
        Level_1_1_Ground();
        void draw(void) override;
        void update(void) override;
        float getWidth(void) override;
        float getHeight(void) override;
        std::shared_ptr<Character> getCharacter() override;
        virtual ~Level_1_1_Ground() = default;
};