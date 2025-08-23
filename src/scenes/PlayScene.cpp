#include "scenes/PlayScene.hpp"
#include "scenes/TitleScene.hpp"
#include "scenes/TimeUpScene.hpp"
#include "scenes/DeathScene.hpp"
#include "scenes/GameOverScene.hpp"
#include "level/Level.hpp"
#include "core/Program.hpp"
#include "core/MusicManager.hpp"
#include "core/SoundManager.hpp"
#include "core/Setting.hpp"
#include "entities/Character.hpp"

bool PlayScene::is2players= false;
bool PlayScene::isMario = true;

PlayScene::PlayScene(const std::string& levelPath) : 
    level(new Level(levelPath)) {
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

    waitTimer = 0.0f;
    waitDuration = 3.0f;
}

void PlayScene::handleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        Program::getInstance().pushScene(new TitleScene());
    }

    Setting::getInstance().handleInput(level);
}

void PlayScene::update() {
    if (Program::getInstance().getSession().TIMELEFT == 0) {
        Program::getInstance().pushScene(new TimeupScene());
        Program::getInstance().getHUD().onNotify(EventType::MARIO_DIED);
        Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
    }

    if (level->getPlayer()->getIsDead()) {
        waitTimer += GetFrameTime();
        
        if (waitTimer >= waitDuration) {
            Program::getInstance().pushScene(new DeathScene());
            if (Program::getInstance().getSession().LIVES == 0) {
                Program::getInstance().pushScene(new GameOverScene());
                Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
                Program::getInstance().getHUD().onNotify(EventType::RESET_LIVES);
                Program::getInstance().getHUD().onNotify(EventType::RESET_SCORES);
            } 
            Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
        }
    } else {
        float deltaTime = GetFrameTime();
        Program::getInstance().getHUD().update(deltaTime);
        level->update();
    }
    
}

void PlayScene::render() {
    level->draw();
    Program::getInstance().getHUD().draw();
    Setting::getInstance().draw();
}