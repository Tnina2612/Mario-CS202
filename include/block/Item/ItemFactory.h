#pragma once
#include "Item.h"
#include "Coin.h"
#include "Flower.h"
#include "HiddenCoin.h"
#include "MushRoom.h"
#include "Star.h"

class SpawnItem
{
public:
    static void CoinSpawner(std::vector<Item *> &items, Vector2 pos);
    static void StarSpawner(std::vector<Item *> &items, Vector2 pos);
    static void HiddenCoinSpawner(std::vector<Item *> &items, Vector2 pos, Character &character);
    static void FlowerSpawner(std::vector<Item *> &items, Vector2 pos);
    static void MushroomSpawner(std::vector<Item *> &items, Vector2 pos, StateMushroom state);
    static void ItemSpawn(const std::string &type_item, std::vector<Item *> &items, Vector2 pos, Character &character);
};
