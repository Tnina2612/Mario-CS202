#include<level/Level.hpp>
#include<cassert>
#include<diy_functions/read.h>

ItemAnimationPoint::ItemAnimationPoint(AnimationItem* item, SubLevel* subLevel) : 
    item(item), subLevel(subLevel) {
    // Constructor
}

void ItemAnimationPoint::read(std::ifstream& inp, std::string filename) {
    readFromFile(inp, filename, 
        detectRec.x, detectRec.y, detectRec.width, detectRec.height, detectType);

    int numAnimations;
    readFromFile(inp, filename, numAnimations);

    for(int i = 0; i < numAnimations; i++) {
        std::string type;
        readFromFile(inp, filename, type);

        if(type == "Down") {
            float targetY;
            readFromFile(inp, filename, targetY);

            animations.push_back(make_shared<ItemDownAnimation>(item, targetY));
        } else if(type == "DestroyBridge") {
            animations.push_back(make_shared<ItemDestroyBridgeAnimation>(item, subLevel->blocks.get(), subLevel->background.get(), subLevel->enemies->getBowser()));
        }
        else {
            throw std::runtime_error("ItemAnimationPoint::read(inp, filename): Unknown item animation type " + type + "\n");
        }
    }
}

void ItemAnimationPoint::saveToFile(std::ofstream& out) {
    out << detectRec.x << ' ' << detectRec.y << ' ' << detectRec.width << ' ' << detectRec.height << ' ' << detectType << endl
        << animations.size() << endl;

    for(int i = 0; i < (int)animations.size(); i++) {
        animations[i]->saveToFile(out);
        out << endl;
    }
}

ItemAnimationManager::ItemAnimationManager(ItemManager* itemManager, SubLevel* subLevel) :
    itemManager(itemManager),
    subLevel(subLevel) {

}

void ItemAnimationManager::draw(void) const {
    for(const std::pair<std::shared_ptr<AnimationItem>, std::shared_ptr<ItemAnimationPoint>>& flag : itemManager->animationObjects) {
        flag.first->draw();
    }
}

void ItemAnimationManager::update(void) {
    if(inAnimation()) {
        todoAnimation.front()->update();

        if(todoAnimation.front()->isDone()) {
            todoAnimation.pop();
        }
    } else {
        for(const std::pair<std::shared_ptr<AnimationItem>, std::shared_ptr<ItemAnimationPoint>>& flag : itemManager->animationObjects) {
            flag.first->update();

            if(isActivate(flag.second) == true) {
                for(int i = 0; i < (int)flag.second->animations.size(); i++) {
                    todoAnimation.push(flag.second->animations[i]);
                }
            }
        }
    }
}

bool ItemAnimationManager::inAnimation(void) const {
    return todoAnimation.size() > 0;
}

bool ItemAnimationManager::isActivate(std::shared_ptr<ItemAnimationPoint> point) {
    if(point == nullptr) return false;
    if(point->detectType == "Touch" && 
        CheckCollisionRecs(itemManager->subLevel->player->getRectangle(), point->detectRec)) return true;
    return false;
}

ItemManager::ItemManager(std::string filename, SubLevel* subLevel) : 
    filename(filename),
    subLevel(subLevel),
    animationManager(this, subLevel) {
    ifstream inp(filename);
    if(inp.is_open() == false) {
        throw std::runtime_error("ItemManager::ItemManager(filename, subLevel) cannot open file: " + filename);
    }

    int numTypes;
    readFromFile(inp, filename, numTypes);
    
    for(int i = 0; i < numTypes; i++) {
        int numItems;
        readFromFile(inp, filename, numItems);

        std::string itemData;
        readFromFile(inp, filename, itemData);
        cout << "Creating " << itemData << endl;

        if(itemData == "movingplatform") {
            for(int j = 0; j < numItems; j++) {
                int type;
                Vector2 startPos, endPos;
                readFromFile(inp, filename, type, startPos.x, startPos.y, endPos.x, endPos.y);

                movingPlatforms.push_back(MovingPlatformFactory::createPlatform(type, startPos, endPos));
                movingPlatforms.back()->setActive(true);
            }
        } else if(itemData.find("flag") == 0 || itemData.find("axe") == 0 || itemData.find("peach") == 0) {
            for(int j = 0; j < numItems; j++) {
                Vector2 pos;
                readFromFile(inp, filename, pos.x, pos.y);

                std::shared_ptr<AnimationItem> item = make_shared<AnimationItem>(itemData, pos);

                std::string hasanimation;
                readFromFile(inp, filename, hasanimation);

                std::shared_ptr<ItemAnimationPoint> animationPoint(nullptr);
                if(hasanimation == "hasanimation") {
                    cout << "Creating new animation" << endl;
                    animationPoint = make_shared<ItemAnimationPoint>(item.get(), subLevel);
                    cout << "Created new animaiton point" << endl;
                    animationPoint->read(inp, filename);
                    cout << "Done new animation" << endl;
                }

                animationObjects.push_back({item, animationPoint});
            }
        } else {
            for(int j = 0; j < numItems; j++) {
                float x, y;
                readFromFile(inp, filename, x, y);

                items.push_back(Item::stringToItem(itemData, x, y));
            }
        }
    }
    inp.close();
}

void ItemManager::draw() {
    animationManager.draw();

    for(const shared_ptr<Item>& item : items) {
        item->draw();
    }

    for(const std::shared_ptr<MovingPlatform> platform : movingPlatforms) {
        platform->draw();
    }
}

void ItemManager::update() {
    if(animationManager.inAnimation()) {
        animationManager.update();
    }
    else {
        animationManager.update();

        // Delete items that are marked for deletion
        for(int i = 0; i < items.size(); i++) {
            if(items[i]->isDelete()) {
                items.erase(items.begin() + i);
                i--;
            }
        }

        Rectangle charRec = subLevel->player->getRectangle();

        // Update items that are added and check if they activate the player's actions
        for(shared_ptr<Item>& item : items) {
            if (item->isAppearAnimation() == false) {
                subLevel->blocks->update(item);
            }
            item->update();
            if(CheckCollisionRecs(charRec, item->getDrawRec())) {
                item->activate(*subLevel->player);
            }
        }

        // Update moving platforms
        for(std::shared_ptr<MovingPlatform>& platform : movingPlatforms) {
            platform->update();
            const Rectangle& platformRec = platform->getRect();
            
            if(CheckCollisionRecs(charRec, platformRec)) {
                if(charRec.y <= platformRec.y) {
                    subLevel->player->setPosition(charRec.x, platformRec.y);
                    subLevel->player->hitBlockBottom();
                }
                else if(charRec.y > platformRec.y)  {
                    subLevel->player->setPosition(charRec.x, platformRec.y + charRec.height + platformRec.height);
                    subLevel->player->hitBlockTop();
                }
            }
        }
    }
}

void ItemManager::addItem(shared_ptr<Item> item) {
    items.push_back(item);
}

void ItemManager::saveToFile(std::string filename) {
    ofstream out(filename);
    if(out.is_open() == false) {
        throw runtime_error("ItemManager::saveToFile(filename) cannot open file " + filename + '\n');
    }
    out << items.size() + movingPlatforms.size() << endl;
    for(int i = 0; i < (int)items.size(); i++) {
        items[i]->saveToFile(out);
    }
    for(int i = 0; i < (int)movingPlatforms.size(); i++) {
        movingPlatforms[i]->saveToFile(out);
    }
    for(int i = 0; i < (int)animationObjects.size(); i++) {
        animationObjects[i].first->saveToFile(out);
        if(animationObjects[i].second == nullptr) {
            out << "noanimation" << endl;
        } else {
            animationObjects[i].second->saveToFile(out);
        }
    }
    out.close();
}