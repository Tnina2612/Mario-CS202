#include "scenes/PlayScene.hpp"
#include "scenes/TitleScene.hpp"
#include "level/Level.hpp"
#include "core/Program.hpp"
#include "core/MusicManager.hpp"
#include "entities/Character.hpp"

PlayScene::PlayScene(const std::string& levelName)
    : level(new Level("./world-maps/" + levelName)) {
}

PlayScene::~PlayScene() {
    delete level;
}

void PlayScene::init() {
    eventManager.addObserver(&Program::getInstance().getHUD());

    switch (LevelVar::ThemeID) {
        case LevelVar::Overworld:
            MusicManager::getInstance().playMusic(MusicType::OVERWORLD);
            break;
        case LevelVar::Underground:
            MusicManager::getInstance().playMusic(MusicType::UNDERGROUND);
            break;
        case LevelVar::Castle:
            MusicManager::getInstance().playMusic(MusicType::CASTLE);
            break;
        case LevelVar::Underwater:
            MusicManager::getInstance().playMusic(MusicType::UNDERWATER);
            break;
        default:
            MusicManager::getInstance().playMusic(MusicType::OVERWORLD);
            break;
    }
}

void PlayScene::handleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        Program::getInstance().pushScene(new TitleScene());
    }
}

void PlayScene::update() {
    level->update();

    float deltaTime = GetFrameTime();
    Program::getInstance().getHUD().update(deltaTime);
}

void PlayScene::render() {
    level->draw();
}