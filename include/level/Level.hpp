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
#include<queue>

struct EnemyList {
    std::vector<std::shared_ptr<Enemy>> list;
    EnemyList(std::string filename);
    ~EnemyList(void) = default;
};

class Level;
class SubLevel;

struct NextSubLevelScene {
    std::string filename;
    std::string worldType;
    Vector2 newPlayerPosition;
};

struct ChangeSubLevelPoint {
    Rectangle detectRec;
    std::string key;
    std::vector<std::shared_ptr<SubLevelAnimation>> animations;
    std::shared_ptr<NextSubLevelScene> nextScene;
};

class ChangeSubLevelManager {
    std::vector<ChangeSubLevelPoint> list;
    SubLevel* subLevel;
public:
    ChangeSubLevelManager(std::string filename, SubLevel* subLevel);
    ~ChangeSubLevelManager(void) = default;
    void update();
    void addAnimation(int id, ifstream& inp);
    bool okToChange(int id);
    void transit(int id);
    void draw() const;
};

class SubLevelPlayerGameplayManager {
    private:
        SubLevel* subLevel;
    public:
        SubLevelPlayerGameplayManager(SubLevel* subLevel);
        void update();
};

class SubLevelPlayerAnimationManager {
    private:
        SubLevel* subLevel;
        std::queue<std::shared_ptr<SubLevelAnimation>> animations;
        std::shared_ptr<NextSubLevelScene> nextScene;
    public:
        SubLevelPlayerAnimationManager(SubLevel* subLevel, std::vector<std::shared_ptr<SubLevelAnimation>> animations, std::shared_ptr<NextSubLevelScene> nextScene);
        void update();
        bool done() const;
};

class SubLevelPlayerManager {
    private:
        SubLevel* subLevel;
        SubLevelPlayerGameplayManager gameplayManager;
        std::unique_ptr<SubLevelPlayerAnimationManager> animationManager;
        InputManager& inputManager;
    public:
        SubLevelPlayerManager(SubLevel* subLevel, InputManager& inputManager);
        void update();
        void addAnimation(unique_ptr<SubLevelPlayerAnimationManager> nextSceneManager);
};

class SubLevel {
        friend class Level;
        friend class ChangeSubLevelManager;
        friend class SubLevelPlayerGameplayManager;
        friend class SubLevelPlayerAnimationManager;
        Level* level;
        Character* player;
        std::shared_ptr<TileMap> background;
        std::shared_ptr<TileMap> blocks;
        std::shared_ptr<EnemyList> enemies;
        std::shared_ptr<ChangeSubLevelManager> changeSubLevelManager;
        SubLevelPlayerManager playerManager;

        bool debug = false;
    public:
        SubLevel(Level* level, std::string folderName, Character* player, InputManager& inputManager);
        void draw();
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
        void changeSubLevel(NextSubLevelScene nextScene);
        void draw(void);
        void update(void);
        ~Level();
};