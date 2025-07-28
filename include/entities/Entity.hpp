#pragma once
#include "../../assets/images/Coordinate.h" 
class Entity {
protected:
    Vector2 pos;
public:
    Entity(Vector2 pos) : pos(pos) {}
    virtual ~Entity() = default;

    virtual void update() = 0;
    virtual void draw() = 0;

    Vector2 getPosition() const { return pos; }
    void setPosition(Vector2 newPos) { pos = newPos; }
};