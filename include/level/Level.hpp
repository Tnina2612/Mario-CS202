#pragma once
#include<level/TileMap.hpp>
#include<raylib.h>
#include<iostream>
#include<entities/Character.hpp>
#include<entities/Mario.hpp>

class Level {
    private:
        std::shared_ptr<TileMap> tileMap;
        std::shared_ptr<Character> character;
    public:
        Level(const std::string& fileName);
        void draw(void);
        void update();
        float getWidth();
        float getHeight();
        std::shared_ptr<Character> getCharacter();
};