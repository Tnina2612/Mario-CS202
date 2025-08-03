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
        subLevel = make_shared<SubLevel>(this, initialWorld);
        nextSubLevel.reset();
    inp.close();
}

void Level::draw(void) {
    BeginTextureMode(renderTexture);
        BeginMode2D(camera);
            subLevel->draw();
            player->draw();
        EndMode2D();
    EndTextureMode();

    DrawTexturePro(renderTexture.texture, Rectangle{0, 0, Global::ORIGINAL_WIDTH, -Global::ORIGINAL_HEIGHT}, Rectangle{0, 0, Global::WINDOW_WIDTH, Global::WINDOW_HEIGHT}, Vector2{0, 0}, 0.f, WHITE);
}

void Level::update(void) {
    // Player update
    inputManager.update();
    if(player->getPos().x < camera.target.x - Global::ORIGINAL_WIDTH / 2.f) player->hitBlockLeft(camera.target.x - Global::ORIGINAL_WIDTH / 2.f);
    if(player->getPos().x + player->getRectangle().width > camera.target.x + Global::ORIGINAL_WIDTH / 2.f) player->hitBlockRight(camera.target.x + Global::ORIGINAL_WIDTH / 2.f);
    subLevel->update(player);
    if(player->getPos().y >= Global::ORIGINAL_HEIGHT) player->die();

    // Sub-level update
    if(nextSubLevel != nullptr) {
        subLevel = move(nextSubLevel);
    }

    // Camera update
    camera.target.x = min(subLevel->blocks->getWidth() * Global::TILE_SIZE - Global::ORIGINAL_WIDTH / 2.f, max(Global::ORIGINAL_WIDTH / 2.f, player->getPos().x + player->getRectangle().width / 2.f));
    camera.target.y = Global::ORIGINAL_HEIGHT / 2.f;
}

void Level::changeSubLevel(ChangeSubLevelPoint point) {
    cout << "World type: " << point.worldType << endl;
    if(point.worldType == "overworld") {
        LevelVar::ThemeID = LevelVar::Overworld;
        LevelVar::BackGroundColor = LevelVar::SkyColor;
    } else if(point.worldType == "underground") {
        LevelVar::ThemeID = LevelVar::Underground;
        LevelVar::BackGroundColor = LevelVar::UndergroundColor;
    }

    nextSubLevel = make_shared<SubLevel>(this, point.filename);

    player->setPosition(point.newPlayerPosition.x, point.newPlayerPosition.y);
}

Level::~Level() {
    UnloadRenderTexture(renderTexture);
}

SubLevel::SubLevel(Level* level, std::string folderName) : // Initializer
    level(level),
    background(make_shared<TileMap>(folderName + "/background.txt")), 
    blocks(make_shared<TileMap>(folderName + "/blocks.txt")),
    enemies(make_shared<EnemyList>(folderName + "/enemies.txt")),
    changeSubLevelPoints(make_shared<ChangeSubLevelPointList>(folderName + "/changingPoints.txt")) {
}

void SubLevel::draw(void) {
    ClearBackground(LevelVar::BackGroundColor);
    background->draw();
    for(const std::shared_ptr<Enemy>& enemy : enemies->list) {
        enemy->draw();
    }
    blocks->draw();
}

void SubLevel::update(std::shared_ptr<Character> player) {
    blocks->update(player);

    // Enemy update
    for(const std::shared_ptr<Enemy>& enemy : enemies->list) {
        // enemy->update();
    }

    // Changing maps
    for(ChangeSubLevelPoint point : changeSubLevelPoints->list) {
        if(CheckCollisionRecs(player->getRectangle(), point.rec)) {
            if(point.key == 'D' && IsKeyPressed(KEY_DOWN)) level->changeSubLevel(point);
            if(point.key == 'L' && IsKeyPressed(KEY_LEFT)) level->changeSubLevel(point);
            if(point.key == 'U' && IsKeyPressed(KEY_UP)) level->changeSubLevel(point);
            if(point.key == 'R' && IsKeyPressed(KEY_RIGHT)) level->changeSubLevel(point);
        }
    }
}