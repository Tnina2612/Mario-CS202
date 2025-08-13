#include "block/Item/Item.h"
#include<block/Item/Coin.h>
#include<block/Item/Mushroom.h>
#include<block/Item/Star.h>
#include<diy_functions/strsplit.h>

Texture2D Item::itemTexture;

Item::Item(Vector2 pos)
    : pos_(pos), frame_(0.0f), type_(0), appearAnimation(1), isDelete_(0) {
    if(itemTexture.id == 0) {
        itemTexture = LoadTexture("./assets/images/sprite-sheets/items.png");
    }
    if(itemTexture.id == 0) {
        throw runtime_error("Item::Item(pos): LoadTexture failed");
    }
}

Vector2 Item::getPos() const { return pos_; }

void Item::setPos(Vector2 pos) { pos_ = pos; }

Rectangle Item::getSourceRec() const { return rec_; }

Rectangle Item::getDrawRec() const { return {pos_.x - rec_.width * 3.0f / 2.0f, pos_.y - rec_.height, rec_.width, rec_.height}; }

bool Item::isAppearAnimation() const { return appearAnimation; }

bool Item::isDelete() const { return isDelete_; }

void Item::draw()
{
    if(appearAnimation == false) return;
    Rectangle dest_rec = {pos_.x, pos_.y, rec_.width, rec_.height};
    DrawTexturePro(itemTexture, rec_, dest_rec, {dest_rec.width / 2.0f, dest_rec.height}, 0.0f, WHITE);
}

std::shared_ptr<Item> Item::stringToItem(std::string itemData, float x, float y) {
    vector<std::string> item = strsplit(itemData, ',');
    std::string name = item[0];
    if(name.find("coin") != std::string::npos) {
            return (make_shared<Coin>(Vector2{x, y}));
    } else if(name.find("super") != std::string::npos) {
        return (make_shared<Mushroom>(Vector2{x, y}, StateMushroom::super_));
    } else if(name.find("1up") != std::string::npos) {
        return (make_shared<Mushroom>(Vector2{x, y}, StateMushroom::one_up));
    } else if(name.find("star") != std::string::npos) {
        return (make_shared<Star>(Vector2{x, y}));
    }
    throw std::runtime_error("Item::stringToItem: name of the item not found.");
}

std::vector<std::shared_ptr<Item>> Item::stringToVectorItem(std::string itemData, float x, float y) {
    std::vector<std::shared_ptr<Item>> items;
    std::vector<std::string> vectorData = strsplit(itemData, ':');
    if(vectorData.size() == 1) {
        return {};
    }
    for(int i = 1; i < (int)vectorData.size(); i++) {
        vector<std::string> item = strsplit(vectorData[i], ',');
        if(item.size() > 2) {
            throw std::runtime_error("Data of a item must have at most two values: (type, quantity)");
        }
        string name = item[0];
        int quantity = 1;
        try {
            if(item.size() == 2) {
                quantity = std::stoi(item[1]);
            }
        } catch (const std::invalid_argument& e) {
            throw std::runtime_error("Invalid quantity value: not a number");
        } catch (const std::out_of_range& e) {
            throw std::runtime_error("Quantity value out of range");
        }
        for(int j = 0; j < quantity; j++) {
            items.push_back(stringToItem(name, x, y));
        }
    }
    return items;
}