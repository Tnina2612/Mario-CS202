#include<level/Level.hpp>

LevelGameplayManager::LevelGameplayManager(SubLevel* subLevel) : subLevel(subLevel) 
{
    // Constructor
}

void LevelGameplayManager::update() {
    // Detect and simulate collision
    pastPlayerRec = subLevel->player->getRectangle();
    subLevel->blocks->update(subLevel->player);
    subLevel->player->update();

    // Detect and change map
    subLevel->changeSubLevelManager->update();
}