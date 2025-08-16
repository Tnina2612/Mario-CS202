#include<level/Level.hpp>
#include<cassert>

ItemManager::ItemManager(std::string filename, SubLevel* subLevel) : subLevel(subLevel) {
    ifstream inp(filename);
    if(inp.is_open() == false) {
        throw std::runtime_error("ItemManager::ItemManager(filename) cannot open file: " + filename);
    }
    int numTypes;
    inp >> numTypes;
    for(int i = 0; i < numTypes; i++) {
        int numItems;
        inp >> numItems;
        std::string itemData;
        inp >> itemData;
        if(itemData == "movingplatform") {
            for(int j = 0; j < numItems; j++) {
                int type;
                Vector2 startPos, endPos;
                inp >> type >> startPos.x >> startPos.y >> endPos.x >> endPos.y;
                movingPlatforms.push_back(MovingPlatformFactory::createPlatform(type, startPos, endPos));
                movingPlatforms.back()->setActive(true);
            }
        } else {
            for(int j = 0; j < numItems; j++) {
                float x, y;
                inp >> x >> y;
                items.push_back(Item::stringToItem(itemData, x, y));
            }
        }
    }
    inp.close();
}

void ItemManager::draw() {
    for(const shared_ptr<Item>& item : items) {
        item->draw();
    }

    for(const std::shared_ptr<MovingPlatform> platform : movingPlatforms) {
        platform->draw();
    }
}

void ItemManager::update() {
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

void ItemManager::addItem(shared_ptr<Item> item) {
    items.push_back(item);
    std::cout << "Item added: " << item->getType() << " at position (" << item->getPos().x << ", " << item->getPos().y << ")" << endl;
}

void ItemManager::saveToFile(std::string filename) {
    ofstream out(filename);
    if(out.is_open() == false) {
        throw runtime_error("ItemManager::saveToFile(filename) cannot open file " + filename + '\n');
    }
    out << items.size() + movingPlatforms.size() << endl;
    for(int i = 0; i < (int)items.size(); i++) {
        out << "1 " << items[i]->getType() << endl;
        out << items[i]->getPos().x << ' ' << items[i]->getPos().y << endl;
    }
    for(int i = 0; i < (int)movingPlatforms.size(); i++) {
        out << "1 movingplatform" << endl;
        out << movingPlatforms[i]->getSizeMovementType() << ' '
            << movingPlatforms[i]->getStartPos().x << ' ' << movingPlatforms[i]->getStartPos().y << ' '
            << movingPlatforms[i]->getEndPos().x << ' ' << movingPlatforms[i]->getEndPos().y << endl;
    }
    out.close();
}