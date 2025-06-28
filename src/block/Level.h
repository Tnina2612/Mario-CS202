#pragma once
#include <vector>
#include "Block.h"

class Level {
private:
    std::vector<Block*> blocks;

public:
    ~Level() {
        for (auto* b : blocks) delete b;
    }

    void AddBlock(Block* b) {
        blocks.push_back(b);
    }

    void Draw() {
        for (auto* b : blocks)
            b->Draw();
    }
};
