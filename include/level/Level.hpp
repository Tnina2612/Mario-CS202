#pragma once
#include<level/TileMap.hpp>
#include<raylib.h>
#include<iostream>

class Level {
    private:
        std::shared_ptr<TileMap> tileMap;
    public:
        Level(const std::string& fileName);
        void draw(void);
};