#include "level/Level.hpp"
#include "core/Program.hpp"
#include "scenes/GameOverScene.hpp"
#include "scenes/TimeUpScene.hpp"
#include "scenes/PlayScene.hpp"
#include <filesystem>
#include <diy_functions/read.h>
#include <core/MusicManager.hpp>

SubLevel::SubLevel(Level* level, std::string folderName, Character* player, Vector2 initPlayerPosition, InputManager& inputManager, Camera2D* camera) : // Initializer
    level(level),
    folderName(folderName),
    background(make_shared<TileMap>(folderName + "/background.txt", this)), 
    blocks(make_shared<TileMap>(folderName + "/blocks.txt", this)),
    player(player), 
    enemies(make_shared<EnemyManager>(folderName + "/enemies.txt", this)),
    initPlayerPosition(initPlayerPosition),
    itemManager(make_shared<ItemManager>(folderName + "/items.txt", this)),
    camera(camera)
{
    playerManager = (make_shared<PlayerManager>(this, inputManager, folderName)); // Need to be construct after blocks
    player->setPosition(initPlayerPosition.x, initPlayerPosition.y);
}

SubLevel::SubLevel(const SubLevel& o) :
    level(NULL),
    player(NULL),
    camera(NULL),
    playerManager(NULL),
    background(make_shared<TileMap>(*o.background)),
    blocks(make_shared<TileMap>(*o.blocks)),
    enemies(make_shared<EnemyManager>(*o.enemies)),
    folderName(o.folderName),
    initPlayerPosition(o.initPlayerPosition) {
}

void SubLevel::connectToLevel(Level* level) {
    this->level = level;
    player = level->player.get();
    camera = &level->camera;
    playerManager = make_shared<PlayerManager>(this, level->inputManager, folderName);
    background->connectToSubLevel(this);
    blocks->connectToSubLevel(this);
    enemies->connectToSubLevel(this); // Need pointer to the player
    itemManager = make_shared<ItemManager>(folderName + "/items.txt", this);
}

void SubLevel::draw() {
    ClearBackground(LevelVar::BackGroundColor);
    background->draw();
    enemies->draw();
    itemManager->draw();
    player->draw();
    blocks->draw();
}

void SubLevel::update() {
    background->updateBlocks();
    enemies->update();
    itemManager->update();
    playerManager->update();
    blocks->updateBlocks();
    // Debug
    if(IsKeyPressed(KEY_Q)) {
        debug ^= 1;
    }
}

CheckPoint Level::MarioCheckPoint = {NULL, NULL, ""};
CheckPoint Level::LuigiCheckPoint = {NULL, NULL, ""};

Level::Level() :
    renderTexture(LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT)),
    camera(Camera2D{Vector2{Global::ORIGINAL_WIDTH / 2.f, Global::ORIGINAL_HEIGHT / 2.f}, Vector2{Global::ORIGINAL_WIDTH / 2.f, Global::ORIGINAL_HEIGHT / 2.f}, 0.f, 1.f}),
    inputManager(INPUT_MANAGER) {
    if (PlayScene::isMario) {
        player = make_shared<Mario>();
    } else {
        player = make_shared<Luigi>();
    }

    LoadCheckPoint();

    // Input manager
    inputManager.addCharacter(player.get());

    inputManager.addKey(KEY_LEFT);
    inputManager.addKey(KEY_RIGHT);
    inputManager.addKey(KEY_UP);
    inputManager.addKey(KEY_DOWN);
    inputManager.addKey(KEY_LEFT_SHIFT);

    inputManager.addListener(new upListener());
    inputManager.addListener(new downListener());
    inputManager.addListener(new leftListener());
    inputManager.addListener(new rightListener());
    inputManager.addListener(new LeftShiftListener());
}

Level::Level(std::string folderName) :
    renderTexture(LoadRenderTexture(Global::ORIGINAL_WIDTH, Global::ORIGINAL_HEIGHT)),
    camera(Camera2D{Vector2{Global::ORIGINAL_WIDTH / 2.f, Global::ORIGINAL_HEIGHT / 2.f}, Vector2{Global::ORIGINAL_WIDTH / 2.f, Global::ORIGINAL_HEIGHT / 2.f}, 0.f, 1.f}),
    inputManager(INPUT_MANAGER),
    folderName(folderName) 
{
    if (PlayScene::isMario) {
        player = make_shared<Mario>();
    } else {
        player = make_shared<Luigi>();
    }

    // Input manager
    inputManager.addCharacter(player.get());

    inputManager.addKey(KEY_LEFT);
    inputManager.addKey(KEY_RIGHT);
    inputManager.addKey(KEY_UP);
    inputManager.addKey(KEY_DOWN);
    inputManager.addKey(KEY_LEFT_SHIFT);

    inputManager.addListener(new upListener());
    inputManager.addListener(new downListener());
    inputManager.addListener(new leftListener());
    inputManager.addListener(new rightListener());
    inputManager.addListener(new LeftShiftListener());

    // Level configurations
    folderName += "/InitializeInstructor.txt";
    ifstream inp(folderName);
    if(inp.is_open() == false) {
        throw runtime_error("Cannot open " + folderName);
    }
        std::string initialWorld;
        readFromFile(inp, folderName, initialWorld);

        std::string theme;
        readFromFile(inp, folderName, theme);
        switchTheme(theme);

        float x, y;
        readFromFile(inp, folderName, x, y);

        player->setPosition(x, y);
        subLevel = make_shared<SubLevel>(this, initialWorld, player.get(), Vector2{x, y}, inputManager, &camera);
        nextSubLevel.reset();
    inp.close();

    // Init checkpoint
    SaveCheckPoint();
}

void Level::LoadCheckPoint()  {
    if(PlayScene::isMario) {
        player = player->clone();

        subLevel = make_shared<SubLevel>(*Level::MarioCheckPoint.subLevel);
        subLevel->connectToLevel(this);

        nextSubLevel = NULL;
        folderName = Level::MarioCheckPoint.folderName;
    } else {
        player = player->clone();

        subLevel = make_shared<SubLevel>(*Level::LuigiCheckPoint.subLevel);
        subLevel->connectToLevel(this);

        nextSubLevel = NULL;
        folderName = Level::LuigiCheckPoint.folderName;
    }
}

void Level::SaveCheckPoint() {
    if(PlayScene::isMario) {
        Level::MarioCheckPoint.player = player->clone();

        Level::MarioCheckPoint.subLevel = make_shared<SubLevel>(*subLevel);

        Level::MarioCheckPoint.folderName = folderName;
    } else {
        Level::LuigiCheckPoint.player = player->clone();

        Level::LuigiCheckPoint.subLevel = make_shared<SubLevel>(*subLevel);

        Level::LuigiCheckPoint.folderName = folderName;
    }
}

void Level::draw(void) {
    BeginTextureMode(renderTexture);
        BeginMode2D(camera);
            subLevel->draw();

            for(const std::tuple<std::string, Vector2, float>& noti : Program::getInstance().getHUD().getInGameNotification()) {
                std::string content = get<0>(noti);
                Vector2 pos = get<1>(noti);
                const float size = 7.f;
                const float space = 0.f;
                DrawTextEx(Program::getInstance().getFont(), content.c_str(), pos, size, space, WHITE);
            }
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
    if(player->getPos().x < camera.target.x - Global::ORIGINAL_WIDTH / 2.f) player->hitBlockLeft();
    if(player->getPos().x + player->getRectangle().width > camera.target.x + Global::ORIGINAL_WIDTH / 2.f) player->hitBlockRight();

    subLevel->update();

    // Camera update
    camera.target.x = min(subLevel->blocks->getWidth() * Global::TILE_SIZE - Global::ORIGINAL_WIDTH / 2.f, max(Global::ORIGINAL_WIDTH / 2.f, player->getPos().x + player->getRectangle().width / 2.f));
    camera.target.y = Global::ORIGINAL_HEIGHT / 2.f;
}

void Level::changeSubLevel(NextSubLevelScene nextScene) {
    switchTheme(nextScene.worldType);
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
    subLevel->itemManager->saveToFile(saveFolder + "/items.txt");
    // Initialize instructor file
    std::string saveFile = saveFolder + "/InitializeInstructor.txt"; 
    ofstream outFile(saveFile);
    if(outFile.is_open()) {
        outFile << getCurrentTheme() << endl;
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

void Level::switchTheme(std::string theme) {
    if(theme == "overworld") {
        LevelVar::ThemeID = LevelVar::Overworld;
        LevelVar::BackGroundColor = LevelVar::SkyColor;
        MusicManager::getInstance().playMusic(MusicType::OVERWORLD);
    } else if(theme == "underground") {
        LevelVar::ThemeID = LevelVar::Underground;
        LevelVar::BackGroundColor = BLACK;
        MusicManager::getInstance().playMusic(MusicType::UNDERGROUND);
    } else if(theme == "castle") {
        LevelVar::ThemeID = LevelVar::Castle;
        LevelVar::BackGroundColor = BLACK;
        MusicManager::getInstance().playMusic(MusicType::CASTLE);
    }
}

std::string Level::getCurrentTheme() {
    switch(LevelVar::ThemeID) {
        case LevelVar::Overworld: return "overworld";
        case LevelVar::Underground: return "underground";
        case LevelVar::Castle: return "castle";
        default: 
            throw runtime_error("Unknown theme ID: " + std::to_string(LevelVar::ThemeID));
    }
}

Level::~Level() {
    UnloadRenderTexture(renderTexture);
}

std::shared_ptr<Character> Level::getPlayer() {
    return player;
}