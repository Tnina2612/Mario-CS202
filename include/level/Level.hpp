#pragma once
#include<level/TileMap.hpp>
#include<level/LevelPlayerAnimation.hpp>
#include<raylib.h>
#include<iostream>
#include<entities/Character.hpp>
#include<entities/Mario.hpp>
#include<entities/Enemy/Enemy.hpp>
#include<entities/Enemy/EnemyFactory.hpp>
#include<core/InputManager.hpp>
#include<core/Global.hpp>

struct EnemyList {
    std::vector<std::shared_ptr<Enemy>> list;
    EnemyList(std::string filename);
    ~EnemyList(void) = default;
};

struct ChangeSubLevelPoint {
    Rectangle rec;
    char key;
    std::string filename;
    std::string worldType;
    Vector2 newPlayerPosition;
};

struct ChangeSubLevelPointList {
    std::vector<ChangeSubLevelPoint> list;
    ChangeSubLevelPointList(std::string filename);
    ~ChangeSubLevelPointList(void) = default;
};

class Level;
class SubLevel;

class SubLevelPlayerCollisionManager {
    private:
        SubLevel* subLevel;
    public:
        SubLevelPlayerCollisionManager(SubLevel* subLevel);
        void update();
};

class SubLevelPlayerNextSceneManager {
    private:
        SubLevel* subLevel;
        unique_ptr<SubLevelAnimation> animation;
        ChangeSubLevelPoint nextScene;
    public:
        SubLevelPlayerNextSceneManager(SubLevel* subLevel, unique_ptr<SubLevelAnimation> animation, ChangeSubLevelPoint nextScene);
        void update();
};

class SubLevelPlayerManager {
    private:
        SubLevel* subLevel;
        SubLevelPlayerCollisionManager collisionManager;
        unique_ptr<SubLevelPlayerNextSceneManager> nextSceneManager;
    public:
        SubLevelPlayerManager(SubLevel* subLevel);
        void update();
        void addNextScene(unique_ptr<SubLevelPlayerNextSceneManager> nextSceneManager);
};

class SubLevel {
        friend class Level;
        friend class SubLevelPlayerCollisionManager;
        friend class SubLevelPlayerNextSceneManager;
        Level* level;
        Character* player;
        std::shared_ptr<TileMap> background;
        std::shared_ptr<TileMap> blocks;
        std::shared_ptr<EnemyList> enemies;
        std::shared_ptr<ChangeSubLevelPointList> changeSubLevelPoints;
        SubLevelPlayerManager playerManager;

        bool debug = false;
        bool oke =false;
    public:
        SubLevel(Level* level, std::string folderName, Character* player);
        void draw();
        void playerGoesIntoDownwardPipe();
        void playerGoesIntoUpwardPipe();
        void playerGoesIntoLeftwardPipe();
        void playerGoesIntoRightwardPipe();
        void update();
        ~SubLevel() = default;
};

class Level {
    private:
        std::shared_ptr<SubLevel> subLevel;
        std::shared_ptr<SubLevel> nextSubLevel;
        std::shared_ptr<Character> player;
        RenderTexture2D renderTexture;
        Camera2D camera;
        InputManager& inputManager;
    public:
        Level(std::string folderName);
        void changeSubLevel(ChangeSubLevelPoint point);
        void draw(void);
        void update(void);
        ~Level();
};