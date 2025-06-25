#pragma once
#include "level/TileMap.hpp"
#include <raylib.h>

class Level {
    public:
        virtual void draw(void) = 0;
};

class Level_1_1_Ground : public Level {
    private:
        TileMap map;
    public:
        Level_1_1_Ground(void);
        void draw(void) override;
};