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

SubLevelPlayerGameplayManager::SubLevelPlayerGameplayManager(SubLevel* subLevel) : subLevel(subLevel) 
{
    // Constructor
}

void SubLevelPlayerGameplayManager::update() {
    // Detect and simulate collision
    subLevel->blocks->update(subLevel->player);
    subLevel->player->update();

    // Detect and change map
    subLevel->changeSubLevelManager->update();
}

SubLevelPlayerAnimationManager::SubLevelPlayerAnimationManager(SubLevel* subLevel, std::vector<std::shared_ptr<SubLevelAnimation>> animations, std::shared_ptr<NextSubLevelScene> nextScene) :
    subLevel(subLevel), nextScene(nextScene)
{
    for(auto& animation : animations) {
        animation->initialize(subLevel->player);
        this->animations.push(animation);
    }
}
void SubLevelPlayerAnimationManager::update() {
    if(animations.empty()) {
        throw runtime_error("Animation queue is empty!\n");
    }
    cout << "Update animation: " << animations.front()->getType() << endl;
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

bool SubLevelPlayerAnimationManager::done() const {
    return animations.empty();
}

SubLevelPlayerManager::SubLevelPlayerManager(SubLevel* subLevel, InputManager& inputManager) : subLevel(subLevel), gameplayManager(subLevel),
    inputManager(inputManager)
{
    // Constructor
}

void SubLevelPlayerManager::update() {
    if(animationManager != nullptr) {
        cout << "Update animation manager" << endl;
        animationManager->update();
        if(animationManager->done()) {
            animationManager.reset();
        }
    } else {
        cout << "Update gameplay manager" << endl;
        inputManager.update();
        gameplayManager.update();
    }
}

void SubLevelPlayerManager::addAnimation(unique_ptr<SubLevelPlayerAnimationManager> nextScene) {
    animationManager = move(nextScene);
}

SubLevel::SubLevel(Level* level, std::string folderName, Character* player, InputManager& inputManager) : // Initializer
    level(level),
    background(make_shared<TileMap>(folderName + "/background.txt")), 
    blocks(make_shared<TileMap>(folderName + "/blocks.txt")),
    enemies(make_shared<EnemyList>(folderName + "/enemies.txt")),
    changeSubLevelManager(make_shared<ChangeSubLevelManager>(folderName + "/changingPoints.txt", this)),
    player(player), 
    playerManager(this, inputManager)
{
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
        changeSubLevelManager->draw();
    }
}

void SubLevel::update() {
    playerManager.update();

    // Enemy update
    for(const std::shared_ptr<Enemy>& enemy : enemies->list) {
        // enemy->update();
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
        subLevel = make_shared<SubLevel>(this, initialWorld, player.get(), inputManager);
        nextSubLevel.reset();

        float x, y;
        inp >> x >> y;
        player->setPosition(x, y);
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
    // Sub-level update
    if(nextSubLevel != nullptr) {
        subLevel = nextSubLevel;
        nextSubLevel.reset();
    }

    // Player update
    if(player->getPos().x < camera.target.x - Global::ORIGINAL_WIDTH / 2.f) player->hitBlockLeft(camera.target.x - Global::ORIGINAL_WIDTH / 2.f);
    if(player->getPos().x + player->getRectangle().width > camera.target.x + Global::ORIGINAL_WIDTH / 2.f) player->hitBlockRight(camera.target.x + Global::ORIGINAL_WIDTH / 2.f);
    subLevel->update();

    // Camera update
    camera.target.x = min(subLevel->blocks->getWidth() * Global::TILE_SIZE - Global::ORIGINAL_WIDTH / 2.f, max(Global::ORIGINAL_WIDTH / 2.f, player->getPos().x + player->getRectangle().width / 2.f));
    camera.target.y = Global::ORIGINAL_HEIGHT / 2.f;
}

void Level::changeSubLevel(NextSubLevelScene nextScene) {
    if(nextScene.worldType == "overworld") {
        LevelVar::ThemeID = LevelVar::Overworld;
        LevelVar::BackGroundColor = LevelVar::SkyColor;
    } else if(nextScene.worldType == "underground") {
        LevelVar::ThemeID = LevelVar::Underground;
        LevelVar::BackGroundColor = LevelVar::UndergroundColor;
    }
    nextSubLevel = make_shared<SubLevel>(this, nextScene.filename, player.get(), inputManager);
    player->setPosition(nextScene.newPlayerPosition.x, nextScene.newPlayerPosition.y);
}

Level::~Level() {
    UnloadRenderTexture(renderTexture);
}