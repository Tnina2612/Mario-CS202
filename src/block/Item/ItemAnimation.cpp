#include<block/Item/ItemAnimation.h>

ItemAnimation::ItemAnimation(AnimationItem* item) : item(item) {
    // Constructor
}

ItemDownAnimation::ItemDownAnimation(AnimationItem* item, float targetY) : ItemAnimation(item), targetY(targetY) {
    // Constructor
}

void ItemDownAnimation::update() {
    Vector2 newPos = item->getPosition();

    newPos.y += velocityY * GetFrameTime();
    if(newPos.y >= targetY) {
        newPos.y = targetY;
    }

    item->setPosition(newPos);
}

bool ItemDownAnimation::isDone(void) const {
    return item->getPosition().y >= targetY;
}

std::string ItemDownAnimation::getType(void) const {
    return "Down";
}

void ItemDownAnimation::saveToFile(ostream& os) const {
    os << getType() << " " << targetY;
}