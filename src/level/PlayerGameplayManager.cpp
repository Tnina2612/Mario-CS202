#include<level/Level.hpp>

PlayerGameplayManager::PlayerGameplayManager(SubLevel* subLevel) : subLevel(subLevel) 
{
    // Constructor
}

void PlayerGameplayManager::update() {
    // Detect and simulate collision
    pastPlayerRec = subLevel->player->getRectangle();
    subLevel->blocks->update(subLevel->player);
    subLevel->player->update();
    subLevel->enemies->updatePlayer();
}