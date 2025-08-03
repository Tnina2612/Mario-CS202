#pragma once
#include<level/TileMap.hpp>
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

class SubLevel {
        friend class Level;
        Level* level;
        std::shared_ptr<TileMap> background;
        std::shared_ptr<TileMap> blocks;
        std::shared_ptr<EnemyList> enemies;
        std::shared_ptr<ChangeSubLevelPointList> changeSubLevelPoints;
    public:
        SubLevel(Level* level, std::string folderName);
        void draw(void);
        void update(std::shared_ptr<Character> player);
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