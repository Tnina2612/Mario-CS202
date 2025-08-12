#include "scenes/PlayScene.hpp"
#include "scenes/TitleScene.hpp"
#include "scenes/TimeUpScene.hpp"
#include "level/Level.hpp"
#include "core/Program.hpp"
#include "core/MusicManager.hpp"
#include "core/Setting.hpp"
#include "entities/Character.hpp"

PlayScene::PlayScene(const std::string& levelName) : 
    level(new Level("./world-maps/" + levelName)) {
}

PlayScene::PlayScene(std::string subLevelFolder, Vector2 playerPosition) :
    level(new Level(subLevelFolder, playerPosition)) {
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

    Setting::getInstance().handleInput();
}

void PlayScene::update() {
    level->update();

    float deltaTime = GetFrameTime();
    Program::getInstance().getHUD().update(deltaTime);

    if (Program::getInstance().getSession().TIMELEFT == 0) {
        Program::getInstance().pushScene(new TimeupScene());
        Program::getInstance().getHUD().onNotify(EventType::MARIO_DIED);
        Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
    }
}

void PlayScene::render() {
    level->draw();
    Program::getInstance().getHUD().draw();
    Setting::getInstance().draw();
}