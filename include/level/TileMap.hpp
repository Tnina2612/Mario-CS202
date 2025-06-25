#pragma once
#include "entities/Block.hpp"
#include<vector>
#include<memory>
#include<string>
#include<fstream>

class TileMap {
    private:
        const static int BLOCKSIZE = 16;
        int height, width;
        // std::vector<std::vector<std::unique_ptr<Block>>> tiles;
    public:
        TileMap(int height, int width);
        void loadFromText(std::string dir);
        void draw(void);
};