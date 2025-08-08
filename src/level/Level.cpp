#include "level/Level.hpp"
#include "core/Program.hpp"
#include "scenes/GameOverScene.hpp"

EnemyList::EnemyList(std::string filename) {
    EnemyFactory::loadAllFrames();
    ifstream inp(filename);
    int numTypes;
    inp >> numTypes;
    for(int i = 0; i < numTypes; i++) {
        int numEnemies;
        inp >> numEnemies;
        string enemyType;
        inp >> enemyType;
        for(int j = 0; j < numEnemies; j++) {
            float x, y; 
            inp >> x >> y;
            list.push_back(EnemyFactory::createEnemy(enemyType, Vector2{x, y}));
            list.back()->setActive(true);
        }
    }
    inp.close();
}

ChangeSubLevelPointList::ChangeSubLevelPointList(std::string filename) {
    ifstream inp(filename);
    int numPoints;
    inp >> numPoints;
    list.resize(numPoints);
    for(int i = 0; i < numPoints; i++) {
        float x, y, width, height;
        inp >> x >> y >> width >> height;
        list[i].rec = Rectangle{x, y, width, height};
        inp >> list[i].key;
        inp.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(inp, list[i].filename);
        inp >> list[i].worldType;
        inp >> list[i].newPlayerPosition.x >> list[i].newPlayerPosition.y;
    }
    inp.close();
}

SubLevelPlayerCollisionManager::SubLevelPlayerCollisionManager(SubLevel* subLevel) : subLevel(subLevel) {}

void SubLevelPlayerCollisionManager::update() {
    // Collision
    subLevel->blocks->update(subLevel->player);
    subLevel->player->update();

    // Changing maps
    for(ChangeSubLevelPoint point : subLevel->changeSubLevelPoints->list) {
        if(CheckCollisionRecs(subLevel->player->getRectangle(), point.rec)) {
            if(point.key == 'D' && IsKeyPressed(KEY_DOWN)) {
                subLevel->playerManager.addNextScene(make_unique<SubLevelPlayerNextSceneManager>(subLevel, 
                    make_unique<PlayerDownPipeAnimation>(subLevel->player), point));
            }
            if(point.key == 'L' && IsKeyPressed(KEY_LEFT)) {
                subLevel->playerManager.addNextScene(make_unique<SubLevelPlayerNextSceneManager>(subLevel, 
                    make_unique<PlayerIntoLeftPipeAnimation>(subLevel->player), point));
            }
            if(point.key == 'U' && IsKeyPressed(KEY_UP)) {
                subLevel->playerManager.addNextScene(make_unique<SubLevelPlayerNextSceneManager>(subLevel, 
                    make_unique<PlayerUpPipeAnimation>(subLevel->player), point));
            }
            if(point.key == 'R' && IsKeyPressed(KEY_RIGHT)) {
                subLevel->playerManager.addNextScene(make_unique<SubLevelPlayerNextSceneManager>(subLevel, 
                    make_unique<PlayerIntoRightPipeAnimation>(subLevel->player), point));
            }
        }
    }
}

SubLevelPlayerNextSceneManager::SubLevelPlayerNextSceneManager(SubLevel* subLevel, unique_ptr<SubLevelAnimation> animation, ChangeSubLevelPoint nextScene) :
    subLevel(subLevel), animation(move(animation)), nextScene(nextScene)
{
    // Constructor
}

void SubLevelPlayerNextSceneManager::update() {
    animation->update();
    if(animation->isDone()) {
        animation.reset();
        subLevel->level->changeSubLevel(nextScene);
    }
}

SubLevelPlayerManager::SubLevelPlayerManager(SubLevel* subLevel) : subLevel(subLevel), collisionManager(subLevel)
{
    // Constructor
}

void SubLevelPlayerManager::update() {
    if(nextSceneManager != nullptr) {
        nextSceneManager->update();
    } else {
        collisionManager.update();
    }
}

void SubLevelPlayerManager::addNextScene(unique_ptr<SubLevelPlayerNextSceneManager> nextScene) {
    if(nextSceneManager != nullptr) {
        throw runtime_error("Another next scene animation is being performed!\n");
    }
    nextSceneManager = move(nextScene);
}

SubLevel::SubLevel(Level* level, std::string folderName, Character* player) : // Initializer
    level(level),
    background(make_shared<TileMap>(folderName + "/background.txt")), 
    blocks(make_shared<TileMap>(folderName + "/blocks.txt")),
    enemies(make_shared<EnemyList>(folderName + "/enemies.txt")),
    changeSubLevelPoints(make_shared<ChangeSubLevelPointList>(folderName + "/changingPoints.txt")),
    player(player), 
    playerManager(this) {
}

void SubLevel::draw() {
    ClearBackground(LevelVar::BackGroundColor);
    background->draw();
    for(const std::shared_ptr<Enemy>& enemy : enemies->list) {
        enemy->draw();
    }
    player->draw();
    blocks->draw();

    // Debug
    if(debug) {
        for(ChangeSubLevelPoint point : changeSubLevelPoints->list) {
            DrawRectangleRec(point.rec, Color{100, 50, 50, 100});
        }
    }
}

void SubLevel::playerGoesIntoDownwardPipe() {
    player->intoPipeAnimation.goDownward();
}

void SubLevel::update() {
    playerManager.update();

    // Enemy update
    if(IsKeyPressed(KEY_SPACE)) {
        oke =!oke;
    }
    if(!oke) {
        return;
    }
    for(const std::shared_ptr<Enemy>& enemy : enemies->list) {
        blocks->update(enemy);
        enemy->update();
    }

    // Debug
    if(IsKeyPressed(KEY_Q)) {
        debug ^= 1;
    }
}

Level::Level(std::string folderName) :
    player(make_shared<Mario>()),
    renderTexture(LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT)),
    camera(Camera2D{Vector2{Global::ORIGINAL_WIDTH / 2.f, Global::ORIGINAL_HEIGHT / 2.f}, Vector2{Global::ORIGINAL_WIDTH / 2.f, Global::ORIGINAL_HEIGHT / 2.f}, 0.f, 1.f}),
    inputManager(INPUT_MANAGER) 
{
    // Input manager
    inputManager.addCharacter(player.get());

    inputManager.addKey(KEY_LEFT);
    inputManager.addKey(KEY_RIGHT);
    inputManager.addKey(KEY_UP);
    inputManager.addKey(KEY_DOWN);

    inputManager.addListener(new upListener());
    inputManager.addListener(new downListener());
    inputManager.addListener(new leftListener());
    inputManager.addListener(new rightListener());

    // Level configurations
    LevelVar::ThemeID = LevelVar::Overworld;
    ifstream inp(folderName + "/InitializeInstructor.txt");
    if(inp.is_open() == false) {
        throw runtime_error("Cannot open " + folderName + "/InitializeInstructor.txt");
    }
        std::string initialWorld;
        getline(inp, initialWorld);
        subLevel = make_shared<SubLevel>(this, initialWorld, player.get());
        nextSubLevel.reset();
    inp.close();
}

void Level::draw(void) {
    BeginTextureMode(renderTexture);
        BeginMode2D(camera);
            subLevel->draw();
        EndMode2D();
    EndTextureMode();

    DrawTexturePro(renderTexture.texture, Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT}, Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT}, Vector2{0, 0}, 0.f, WHITE);
}

void Level::update(void) {
    // Player update
    inputManager.update();
    if(player->getPos().x < camera.target.x - Global::ORIGINAL_WIDTH / 2.f) player->hitBlockLeft(camera.target.x - Global::ORIGINAL_WIDTH / 2.f);
    if(player->getPos().x + player->getRectangle().width > camera.target.x + Global::ORIGINAL_WIDTH / 2.f) player->hitBlockRight(camera.target.x + Global::ORIGINAL_WIDTH / 2.f);
    subLevel->update();

    // Sub-level update
    if(nextSubLevel != nullptr) {
        subLevel = move(nextSubLevel);
    }

    // Camera update
    camera.target.x = min(subLevel->blocks->getWidth() * Global::TILE_SIZE - Global::ORIGINAL_WIDTH / 2.f, max(Global::ORIGINAL_WIDTH / 2.f, player->getPos().x + player->getRectangle().width / 2.f));
    camera.target.y = Global::ORIGINAL_HEIGHT / 2.f;
}

void Level::changeSubLevel(ChangeSubLevelPoint point) {
    if(point.worldType == "overworld") {
        LevelVar::ThemeID = LevelVar::Overworld;
        LevelVar::BackGroundColor = LevelVar::SkyColor;
    } else if(point.worldType == "underground") {
        LevelVar::ThemeID = LevelVar::Underground;
        LevelVar::BackGroundColor = LevelVar::UndergroundColor;
    }

    nextSubLevel = make_shared<SubLevel>(this, point.filename, player.get());

    player->setPosition(point.newPlayerPosition.x, point.newPlayerPosition.y);
}

Level::~Level() {
    UnloadRenderTexture(renderTexture);
}