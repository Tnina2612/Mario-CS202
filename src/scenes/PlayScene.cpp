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

bool PlayScene::isTwoPlayers = false;
bool PlayScene::isMario = true;
bool PlayScene::isInitMarioGame = false;
bool PlayScene::isInitLuigiGame = false;

PlayScene::PlayScene() :
    level(new Level()) {
    // Default constructor
}

PlayScene::PlayScene(const std::string& levelPath) : 
    level(new Level(levelPath)) {
    if(isMario == true && isInitMarioGame == false) isInitMarioGame = true;
    if(isMario == false && isInitLuigiGame == false) isInitLuigiGame = true;
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
            if (Program::getInstance().getSession().LIVES == 0) {
                Program::getInstance().pushScene(new GameOverScene());
                Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
            } else {
                Program::getInstance().pushScene(new DeathScene());
                Program::getInstance().getHUD().onNotify(EventType::RESET_TIMER);
            }
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