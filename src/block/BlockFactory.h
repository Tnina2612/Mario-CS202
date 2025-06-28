// BlockFactory.h
#pragma once
#include <map>
#include <string>
#include "Block.h"

class BlockFactory {
private:
    static std::map<std::string, Block*> blockPrototypes;

public:
    static void Init();
    static Block* CreateBlock(const std::string& type, float x, float y);
    static void CleanUp();
};
