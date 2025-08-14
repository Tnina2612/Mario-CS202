#pragma once
#include<block/Block.h>
#include<entities/Enemy/Enemy.hpp>
#include<entities/Enemy/EnemyFactory.hpp>
#include<vector>
#include<memory>
#include<string>
#include<fstream>
#include<iostream>
#include<entities/Character.hpp>

class SubLevel;

class TileMap {
    private:
        constexpr static float BLOCKSIDE = 16.f;
        int height, width;
        std::vector<std::vector<std::shared_ptr<Block>>> tiles;
        SubLevel* subLevel;
        bool debug = false;
        std::vector<Rectangle> debugBlocks;
        std::vector<Rectangle> mergeBlock;

        bool preventFalling(std::shared_ptr<Enemy> enemy, Vector2& movement);
    public:
        TileMap(std::string filename, SubLevel* subLevel);
        void draw(void);
        void updateBlocks();
        void update(Character* character);
        void update(std::shared_ptr<Enemy> enemy);
        void update(std::shared_ptr<Item> item);
        static std::vector<std::pair<int, int>> cellsToCheck(const Rectangle& rec);
        void saveToFile(const std::string& filename) const;

        float getWidth();
        float getHeight();
};