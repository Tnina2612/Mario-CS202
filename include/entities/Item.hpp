#pragma once
#include "Entity.hpp"
#include "Animation.hpp"

enum class ItemType {
    MUSHROOM,
    FLOWER,
    STAR
};

class Item : public Entity {
protected:
    ItemType type;
    Animation animation;
    bool collected = false;
public:
    Item(Vector2 pos, ItemType type, const Animation& anim)
        : Entity(pos), type(type), animation(anim) {}

    virtual ~Item() = default;

    virtual void update() override = 0;
    virtual void draw() override {
        if (!collected)
            animation.draw(pos);
    }

    ItemType getType() const { return type; }
    bool isCollected() const { return collected; }
    void collect() { collected = true; }
};

class Mushroom : public Item {
public:
    Mushroom(Vector2 pos, const Animation& anim)
        : Item(pos, ItemType::MUSHROOM, anim) {}

    void update() override;
};


class Flower : public Item {
public:
    Flower(Vector2 pos, const Animation& anim)
        : Item(pos, ItemType::FLOWER, anim) {}

    void update() override;
};


class Star : public Item {
public:
    Star(Vector2 pos, const Animation& anim)
        : Item(pos, ItemType::STAR, anim) {}

    void update() override;
};