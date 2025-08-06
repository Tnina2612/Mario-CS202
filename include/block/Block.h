#pragma once
#include<raylib.h>
#include<map>
#include<string>
#include<memory>
#include <cmath>
class BlockFlyweight {
    private:
        std::string type;
        Texture2D texture;
    public:
        BlockFlyweight(const char* dir);
        void Draw(int posX, int posY);
        std::string getType();
        ~BlockFlyweight(void);
};

class Block {
protected:
    Vector2 position;
    std::shared_ptr<BlockFlyweight> flyweight;
public:
    Block(Vector2 position, std::shared_ptr<BlockFlyweight> flyweight);
    virtual ~Block() = default;
    virtual void Draw();
    virtual Rectangle getRectangle() const;
    virtual void jiggle() {}
    virtual bool breakBrick() { return false; }
    std::string getType();
};

class BlockFlyweightFactory {
private:
    std::map<std::string, std::shared_ptr<BlockFlyweight>> flyweights;
public:
    std::shared_ptr<BlockFlyweight> getBlockFlyweight(const std::string& type);
};

class BrickBlock : public Block {
protected:
    bool isBroken = false;
    float jiggleOffset = 0.0f;
    float jiggleTime = 0.0f;
public:
    using Block::Block;
    Rectangle getRectangle() const override;
    void jiggle() override;
    bool breakBrick() override;
    void update(float deltaTime);
    void Draw() override;
};

class QuestionBlock : public Block {
protected:
    bool isUsed = false;
    float jiggleOffset = 0.0f;
    float jiggleTime = 0.0f;
public:
    using Block::Block;
    Rectangle getRectangle() const override;
    void jiggle() override;
    bool breakBrick() override; 
    void update(float deltaTime);
    void Draw() override;
};

class GroundBlock : public Block {
public:
    using Block::Block;
    Rectangle getRectangle() const override;
    
};