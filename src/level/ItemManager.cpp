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
        for(int j = 0; j < numItems; j++) {
            float x, y;
            inp >> x >> y;
            items.push_back(Item::stringToItem(itemData, x, y));
        }
    }
    inp.close();
}

void ItemManager::draw() {
    for(const shared_ptr<Item>& item : items) {
        item->draw();
    }
}

void ItemManager::update() {
    for(int i = 0; i < items.size(); i++) {
        if(items[i]->isDelete()) {
            items.erase(items.begin() + i);
            i--;
        }
    }
    for(shared_ptr<Item>& item : items) {
        if (subLevel && subLevel->blocks && item->isAppearAnimation() == false) {
            subLevel->blocks->update(item);
        }
        item->update();
        if(CheckCollisionRecs(subLevel->player->getRectangle(), item->getDrawRec())) {
            item->activate(*subLevel->player);
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
    out << items.size() << endl;
    for(int i = 0; i < (int)items.size(); i++) {
        int j;
        for(j = i + 1; j < (int)items.size(); ) {
            if(items[j]->getType() == items[i]->getType()) {
                j++;
            } else {
                break;
            }
        }
        out << j - i << ' ' << items[i]->getType() << endl;
        for( ; i < j; i++) {
            out << items[i]->getPos().x << ' ' << items[i]->getPos().y << endl;
        }
        i--;
    }
    out.close();
}