#include<level/Level.hpp>

PlayerManager::PlayerManager(SubLevel* subLevel, InputManager& inputManager, std::string folderName) : 
    subLevel(subLevel), gameplayManager(subLevel), 
    inputManager(inputManager),
    animationManager(folderName + "/playerAnimationPoints.txt", subLevel)
{
    // Constructor
}

void PlayerManager::update() {
    if(animationManager.inAnimation() == true) {
        animationManager.update();
    } else {
        inputManager.update();
        gameplayManager.update();
        animationManager.update();
    }
}