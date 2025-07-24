#include "scenes/PlayScene.hpp"
#include "scenes/TitleScene.hpp"
#include "level/Level.hpp"
#include "core/Program.hpp"
#include "entities/Character.hpp"

PlayScene::~PlayScene() {
    delete level;
}

void PlayScene::init() {
    level = new Level_1_1_Ground();
    eventManager.addObserver(&Program::getInstance().getHUD());
}

void PlayScene::handleInput() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        Program::getInstance().changeScene(new TitleScene());
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