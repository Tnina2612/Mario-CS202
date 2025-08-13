#include "level/Level.hpp"
#include "core/Program.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/TimeUpScene.hpp"
#include <filesystem>

SubLevel::SubLevel(Level* level, std::string folderName, Character* player, Vector2 initPlayerPosition, InputManager& inputManager, Camera2D* camera) : // Initializer
    level(level),
    background(make_shared<TileMap>(folderName + "/background.txt", this)), 
    blocks(make_shared<TileMap>(folderName + "/blocks.txt", this)),
    enemies(make_shared<EnemyManager>(folderName + "/enemies.txt", this)),
    changeSubLevelManager(make_shared<ChangeSubLevelManager>(folderName + "/changingPoints.txt", this)),
    player(player), 
    initPlayerPosition(initPlayerPosition),
    playerManager(this, inputManager),
    itemManager(folderName + "/items.txt", this),
    camera(camera),
    folderName(folderName)
{
    player->setPosition(initPlayerPosition.x, initPlayerPosition.y);
}

void SubLevel::draw() {
    ClearBackground(LevelVar::BackGroundColor);
    background->draw();
    enemies->draw();
    itemManager.draw();
    player->draw();
    blocks->draw();

    // Debug
    if(debug) {
        changeSubLevelManager->draw();
    }
}

void SubLevel::update() {
    background->updateBlocks();
    if(player->getGrowthUp() == false && player->getShrinkDown() == false) {
        enemies->update();
    }
    itemManager.update();
    playerManager.update();
    blocks->updateBlocks();

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
        float x, y;
        inp >> x >> y;
        player->setPosition(x, y);
        subLevel = make_shared<SubLevel>(this, initialWorld, player.get(), Vector2{x, y}, inputManager, &camera);
        nextSubLevel.reset();
    inp.close();
}

Level::Level(std::string subLevelFolder, Vector2 playerPosition) :
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
    subLevel = make_shared<SubLevel>(this, subLevelFolder, player.get(), playerPosition, inputManager, &camera);
    nextSubLevel.reset();
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
    nextSubLevel = make_shared<SubLevel>(this, nextScene.filename, player.get(), nextScene.newPlayerPosition, inputManager, &camera);
}

void Level::saveGame(std::string folderName) {
    // Create save folder
    std::string saveFolder = "./savedMaps/" + folderName;
    if(!std::filesystem::exists(saveFolder)) {
        std::filesystem::create_directories(saveFolder);
    }
    subLevel->background->saveToFile(saveFolder + "/background.txt");
    subLevel->blocks->saveToFile(saveFolder + "/blocks.txt");
    subLevel->enemies->saveToFile(saveFolder + "/enemies.txt");
    subLevel->changeSubLevelManager->saveToFile(saveFolder + "/changingPoints.txt");
    // Initialize instructor file
    ofstream outFile(saveFolder + "/InitializeInstructor.txt");
    if(outFile.is_open()) {
        outFile << saveFolder << endl;
        outFile << player->getPos().x << " " << player->getPos().y << endl;
        outFile.close();
    } else {
        throw runtime_error("Cannot open " + saveFolder + "/InitializeInstructor.txt for writing");
    }
}

vector<std::pair<std::string, std::string>> Level::getSavedLevels() {
    vector<std::pair<std::string, std::string>> savedLevels;
    for(const auto& entry : std::filesystem::directory_iterator("./savedMaps")) {
        if(entry.is_directory()) {
            std::string folderName = entry.path().filename().string();
            std::string directory = entry.path().string();
            savedLevels.emplace_back(folderName, directory);
        }
    }
    return savedLevels;
}

Level::~Level() {
    UnloadRenderTexture(renderTexture);
}

std::shared_ptr<Character> Level::getPlayer() {
    return player;
}