#include<level/Level.hpp>

ItemManager::ItemManager(std::string filename) {
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
    for(const shared_ptr<Item>& item : items) {
        item->update();
    }
}