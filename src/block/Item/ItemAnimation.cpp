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

ItemDestroyBridgeAnimation::ItemDestroyBridgeAnimation(AnimationItem* item, TileMap * const blocks,
    TileMap * const background, Bowser * const bowser) : 
    ItemAnimation(item), blocks(blocks), background(background), bowser(bowser) {
    if(item == nullptr || blocks == nullptr || background == nullptr || bowser == nullptr) {
        throw std::runtime_error("ItemDestroyBridgeAnimation constructor: these pointer cannot be NULL\n");
    }
    for(int i = 0; i < blocks->getHeight(); i++) {
        for(int j = 0; j < blocks->getWidth(); j++) {
            if(blocks->getTileNameAt(i, j) == "S10" || blocks->getTileNameAt(i, j) == "P19") {
                blocksToBeErased.push_back({i, j});
            }
        }
    }
    for(int i = 0; i < blocks->getHeight(); i++) {
        for(int j = 0; j < blocks->getWidth(); j++) {
            if(background->getTileNameAt(i, j) == "S10" || background->getTileNameAt(i, j) == "P19") {
                backgroundToBeErased.push_back({i, j});
            }
        }
    }
}

void ItemDestroyBridgeAnimation::update(void) {
    if(backgroundToBeErased.size() > 0) {
        background->erase(backgroundToBeErased.back());
        backgroundToBeErased.pop_back();
    } else if(blocksToBeErased.size() > 0) {
        blocks->erase(blocksToBeErased.back());
        blocksToBeErased.pop_back();
    } else if(bowser->getPos().y < 240) {
        Vector2 newPos = bowser->getPos();
        fallVelocity += fallAcceleration * GetFrameTime();
        newPos.y += fallVelocity * GetFrameTime();
        bowser->setPosition(newPos);
    } else {
        bowser->setActive(false);
        item->vanish();
    }
}

bool ItemDestroyBridgeAnimation::isDone(void) const {
    return backgroundToBeErased.empty() && blocksToBeErased.empty() && bowser->getPos().y >= 240 && item->isVanishing();
}

std::string ItemDestroyBridgeAnimation::getType(void) const {
    return "DestroyBridge";
}

void ItemDestroyBridgeAnimation::saveToFile(ostream& os) const {
    os << getType();
}