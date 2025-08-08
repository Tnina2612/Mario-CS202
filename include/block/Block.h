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
    SpriteSheet sprite_;

    BlockState *questionState_;
    BlockState *normalState_;
    BlockState *solidState_;
    BlockState *breakState_;

    BlockState *currentState_;

    Vector2 pos_;
    int itemCount;
    std::string typeItem;

public:
    Block(Vector2 pos, int itemCount, const std::string &typeItem, const std::string &typeBlock);
    ~Block();
    std::vector<bool> Surrounded_Block{0, 0, 0, 0}; // top bot left right
    void update_();
    void draw_();
    void onHit(std::vector<Item *> &item, Character & character) override;

    void setState(BlockState *new_state);

    Vector2 getPos() const;
    void setPos(Vector2 pos);
    int getItemCount() const;
    Rectangle getSourceRec() const;
    Rectangle getDrawRec() const;
    bool getElapse() const;
    bool getIsDelete() const;
    std::string getTypeItem() const;
    void decreaseItem();

    const SpriteSheet &getSprite();

    BlockState *getQuestionState() const;
    BlockState *getNormalState() const;
    BlockState *getSolidState() const;
    BlockState *getBreakState() const;
};