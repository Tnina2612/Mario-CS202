#include "level/Level.hpp"

Level_1_1_Ground::Level_1_1_Ground() : background("./world-maps/1-1-Ground/background.txt"), 
    blocks("./world-maps/1-1-Ground/blocks.txt"),
    player(make_shared<Mario>()),
    inputManager(INPUT_MANAGER) {
    cout << "Mario's height: " << player->getRectangle().height << '\n';
    cout << "Mario's width: " << player->getRectangle().width << '\n';
    cout << "Mario's x: " << player->getRectangle().x << '\n';
    cout << "Mario's y: " << player->getRectangle().y << '\n';
    {
        EnemyFactory::loadAllFrames();
        ifstream inp("./world-maps/1-1-Ground/enemies.txt");
        int numTypes;
        inp >> numTypes;
        for(int i = 0; i < numTypes; i++) {
            int numEnemies;
            inp >> numEnemies;
            string enemyType;
            inp >> enemyType;
            for(int j = 0; j < numEnemies; j++) {
                int y, x; 
                inp >> y >> x;
                float posX = x * BLOCKSIDE;
                float posY = y * BLOCKSIDE;
                enemies.push_back(EnemyFactory::createEnemy(enemyType, Vector2{posX, posY}));
                enemies.back()->setActive(true);
            }
        }
        inp.close();
    }

    renderTexture = LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT);
    if(IsRenderTextureReady(renderTexture) == false) {
        throw runtime_error("Fail to load renderTexture");
    }

    camera.target.x = Global::ORIGINAL_WIDTH / 2.f;
    camera.target.y = Global::ORIGINAL_HEIGHT / 2.f;
    camera.offset.x = Global::ORIGINAL_WIDTH / 2.f;
    camera.offset.y = Global::ORIGINAL_HEIGHT / 2.f;
    camera.rotation = 0.f;
    camera.zoom = 1.f;

    inputManager.addCharacter(player.get());

    inputManager.addKey(KEY_LEFT);
    inputManager.addKey(KEY_RIGHT);
    inputManager.addKey(KEY_UP);
    inputManager.addKey(KEY_DOWN);

    inputManager.addListener(new upListener());
    inputManager.addListener(new downListener());
    inputManager.addListener(new leftListener());
    inputManager.addListener(new rightListener());
}

void Level_1_1_Ground::draw(void) {
    BeginTextureMode(renderTexture);
        ClearBackground(LevelVar::SkyColor);
        BeginMode2D(camera);
            background.draw();
            blocks.draw();
            player->draw();
            for(std::shared_ptr<Enemy> enemy : enemies) {
                enemy->draw();
            }
        EndMode2D();
    EndTextureMode();
    DrawTexturePro(renderTexture.texture, 
        Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT},
        Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT},
        Vector2{0, 0}, 0, WHITE);
}

void Level_1_1_Ground::update(void) {
    inputManager.update();
    blocks.update(player);
    player->update();
    camera.target.x = min(blocks.getWidth() * BLOCKSIDE - Global::ORIGINAL_WIDTH / 2.f, max(Global::ORIGINAL_WIDTH / 2.f, player->getPos().x + 8.f));
    camera.target.y = Global::ORIGINAL_HEIGHT / 2.f;
}

Level_1_1_Ground::~Level_1_1_Ground() {
    UnloadRenderTexture(renderTexture);
}