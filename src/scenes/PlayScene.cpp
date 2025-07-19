#include "scenes/PlayScene.hpp"
#include "scenes/TitleScene.hpp"
#include "level/Level.hpp"
#include "core/Program.hpp"
#include "entities/Character.hpp"

PlayScene::~PlayScene() {
    delete level;
}

void PlayScene::init() {
    level = new Level("1-1-ground.txt");
    character = level->getCharacter();

    eventManager.addObserver(&Program::getInstance().getHUD());

    // Setup Camera2D
    camera.offset = { Global::WINDOW_WIDTH / 2.0f, 0 }; 
    camera.zoom = 1.0f;
    camera.rotation = 0.0f;

    renderTexture = LoadRenderTexture(level->getWidth()/Global::SCALE_FACTOR, level->getHeight()/Global::SCALE_FACTOR);

    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        level->draw(); // Draw at original 16px tile size
    EndTextureMode();
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

    setUpCamera();
}

void PlayScene::render() {
    float cameraOffsetX = camera.target.x - camera.offset.x;
    float cameraOffsetY = camera.target.y - camera.offset.y;

    // Draw level tiles first (background)
    DrawTexturePro(renderTexture.texture, 
            Rectangle{0, 0, level->getWidth()/Global::SCALE_FACTOR, -level->getHeight()/Global::SCALE_FACTOR},
            Rectangle{-cameraOffsetX, -cameraOffsetY, level->getWidth(), level->getHeight()},
            Vector2{0, 0}, 0, WHITE);

    BeginMode2D(camera);
        level->getCharacter()->draw();
    EndMode2D();
}

void PlayScene::setUpCamera() {
    // Update camera to follow Mario
    float targetX = level->getCharacter()->getPos().x;

    // Prevent camera from showing outside level bounds
    if (targetX < Global::WINDOW_WIDTH / 2.0f) {
        targetX = Global::WINDOW_WIDTH / 2.0f;
    } else if (targetX > level->getWidth() - Global::WINDOW_WIDTH / 2.0f) {
        targetX = level->getWidth() - Global::WINDOW_WIDTH / 2.0f;
    }

    // Lock camera vertically
    camera.target = { targetX, 0 };
}