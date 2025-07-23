#pragma once
#include<block/Block.h>
#include<entities/Character.hpp>
#include<entities/Enemy/Enemy.hpp>
#include<entities/Enemy/EnemyFactory.hpp>
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
        std::vector<std::vector<std::shared_ptr<Block>>> blockTiles;
        std::vector<std::shared_ptr<Enemy>> enemies;
        BlockFlyweightFactory blockFlyweightFactory;
    public:
        TileMap(std::string filename);
        void draw(void);
        void update(std::shared_ptr<Character> character);

        float getWidth();
        float getHeight();
};