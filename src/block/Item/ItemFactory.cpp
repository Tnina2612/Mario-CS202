#include "Item/ItemFactory.h"

void SpawnItem::CoinSpawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Coin(pos));
}

void SpawnItem::StarSpawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Star(pos));
}

void SpawnItem::HiddenCoinSpawner(std::vector<Item *> &items, Vector2 pos, Character& character)
{
    items.push_back(new HiddenCoin(pos));
    items.back()->activate(character);
}

void SpawnItem::FlowerSpawner(std::vector<Item *> &items, Vector2 pos)
{
    items.push_back(new Flower(pos));
}

void SpawnItem::MushroomSpawner(std::vector<Item *> &items, Vector2 pos, StateMushroom state)
{
    items.push_back(new Mushroom(pos, state));
}

// void SpawnItem::ItemSpawn(const std::string &type_item, std::vector<Item *> &items, Vector2 pos, Character &character)
// {
//     if (type_item == "flower" || type_item == "super_mushroom")
//     {
//         if (player.get_form() == PlayerForm::Small)
//             MushroomSpawner(items, pos, StateMushRoom::super_);
//         else
//             FlowerSpawner(items, pos);
//     }
//     if (type_item == "hidden_coin")
//         HiddenCoinSpawner(items, pos, character);
//     if (type_item == "one_up_mushroom")
//         MushroomSpawner(items, pos, StateMushRoom::one_up);
//     if (type_item == "posion_mushroom")
//         MushroomSpawner(items, pos, StateMushRoom::posion_);
//     if (type_item == "star")
//         StarSpawner(items, pos);
// }