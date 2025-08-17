#include<block/Item/AnimationItem.h>

AnimationItem::AnimationItem(std::string name, Vector2 pos) : 
    name(name),
    pos(pos),
    animation(name) {
}

void AnimationItem::update() {
    animation.update();
}

void AnimationItem::draw() const {
    animation.draw(pos.x, pos.y);
}

void AnimationItem::setPosition(Vector2 newPos) {
    pos = newPos;
}

Vector2 AnimationItem::getPosition(void) const {
    return pos;
}

void AnimationItem::saveToFile(std::ofstream& out) const {
    out << "1  " << name << endl
        << pos.x << ' ' << pos.y << endl;
}