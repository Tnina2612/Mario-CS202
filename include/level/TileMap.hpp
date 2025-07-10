#pragma once
#include<block/Block.h>
#include<vector>
#include<memory>
#include<string>
#include<fstream>
#include<iostream>

class TileMap {
    private:
        const static int BLOCKSIDE = 16;
        int height, width;
        std::vector<std::vector<std::shared_ptr<Block>>> backgroundTiles;
        std::vector<std::vector<std::shared_ptr<Block>>> objectTiles;
        BlockFlyweightFactory blockFlyweightFactory;
    public:
        TileMap(std::string filename);
        void draw(void);
};