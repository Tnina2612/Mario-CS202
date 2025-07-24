#pragma once
#include<level/TileMap.hpp>
#include<raylib.h>
#include<iostream>
#include<entities/Character.hpp>
#include<entities/Mario.hpp>
#include<core/InputManager.hpp>
#include<core/Global.hpp>

class Level {
    private:
        std::shared_ptr<TileMap> tileMap;
        std::shared_ptr<Character> player;
        InputManager& inputManager;
    public:
        Level(const std::string& fileName);
        void draw(void);
        void update();
        float getWidth();
        float getHeight();
        std::shared_ptr<Character> getCharacter();
};