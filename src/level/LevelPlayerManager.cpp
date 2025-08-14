#include<level/Level.hpp>

LevelPlayerManager::LevelPlayerManager(SubLevel* subLevel, InputManager& inputManager) : subLevel(subLevel), gameplayManager(subLevel),
    inputManager(inputManager)
{
    // Constructor
}

void LevelPlayerManager::update() {
    if(animationManager != nullptr) {
        animationManager->update();
        if(animationManager->done()) {
            animationManager.reset();
        }
    } else {
        inputManager.update();
        gameplayManager.update();
    }
}

void LevelPlayerManager::addAnimation(unique_ptr<LevelPlayerAnimationManager> nextScene) {
    animationManager = move(nextScene);
}

bool LevelPlayerManager::hasAnimation() const {
    return animationManager != nullptr;
}