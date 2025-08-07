#include<level/Level.hpp>

LevelPlayerAnimationManager::LevelPlayerAnimationManager(SubLevel* subLevel, std::vector<std::shared_ptr<SubLevelAnimation>> animations, std::shared_ptr<NextSubLevelScene> nextScene) :
    subLevel(subLevel), nextScene(nextScene)
{
    for(auto& animation : animations) {
        animation->initialize(subLevel->player);
        this->animations.push(animation);
    }
}
void LevelPlayerAnimationManager::update() {
    if(animations.empty()) {
        throw runtime_error("Animation queue is empty!\n");
    }
    animations.front()->update();
    if(animations.front()->isDone()) {
        animations.pop();
    }
    if(animations.empty()) {
        if(nextScene != nullptr) {
            subLevel->level->changeSubLevel(*nextScene.get());
        }
    }
}

bool LevelPlayerAnimationManager::done() const {
    return animations.empty();
}