#pragma once
#include<raylib.h>
#include<map>
#include<string>
#include<memory>

class BlockFlyweight {
    private:
        Texture2D texture;
    public:
        BlockFlyweight(const char* dir);
        void Draw(int posX, int posY);
        ~BlockFlyweight(void);
};

class Block {
protected:
    Vector2 position;
    std::shared_ptr<BlockFlyweight> flyweight;

public:
    Block(Vector2 position, std::shared_ptr<BlockFlyweight> flyweight);
    virtual ~Block() = default;
    void Draw();
};

class BlockFlyweightFactory {
private:
    std::map<std::string, std::shared_ptr<BlockFlyweight>> flyweights;
public:
    std::shared_ptr<BlockFlyweight> getBlockFlyweight(const std::string& type);
};
