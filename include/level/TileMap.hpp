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
        std::vector<std::vector<std::shared_ptr<Block>>> tiles;
        BlockFlyweightFactory tileFactory;

        bool debug;
        std::vector<Rectangle> debugBlocks;
        std::vector<Rectangle> mergeBlock;
    public:
        TileMap(std::string filename);
        void draw(void);
        void update(std::shared_ptr<Character> character);
        void update(std::shared_ptr<Enemy> enemy);
        void update(std::shared_ptr<Enemy> enemy, std::shared_ptr<Block> block);
        std::vector<std::pair<int, int>> cellsToCheck(const Rectangle& rec);

        float getWidth();
        float getHeight();
};