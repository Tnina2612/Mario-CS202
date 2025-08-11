#pragma once
#include<level/TileMap.hpp>
#include<level/LevelPlayerAnimation.hpp>
#include<entities/Enemy/Enemy.hpp>
#include<entities/Enemy/EnemyFactory.hpp>
#include<raylib.h>
#include<iostream>
#include<entities/Character.hpp>
#include<entities/Mario.hpp>
#include<core/InputManager.hpp>
#include<core/Global.hpp>
#include<queue>

class Level;
class SubLevel;

class EnemyManager {
    std::vector<std::shared_ptr<Enemy>> list;
    SubLevel* subLevel;
public:
    EnemyManager(std::string filename, SubLevel* subLevel);
    void update();
    void draw() const;
    void saveToFile(std::string filename);
    ~EnemyManager(void) = default;
};

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
    void saveToFile(std::string filename) const;
};

class LevelGameplayManager {
    private:
        friend class EnemyManager;
        SubLevel* subLevel;
        Rectangle pastPlayerRec;
    public:
        LevelGameplayManager(SubLevel* subLevel);
        void update();
};

class LevelPlayerAnimationManager {
    private:
        SubLevel* subLevel;
        std::queue<std::shared_ptr<SubLevelAnimation>> animations;
        std::shared_ptr<NextSubLevelScene> nextScene;
    public:
        LevelPlayerAnimationManager(SubLevel* subLevel, std::vector<std::shared_ptr<SubLevelAnimation>> animations, std::shared_ptr<NextSubLevelScene> nextScene);
        void update();
        bool done() const;
};

class LevelPlayerManager {
    private:
        friend class EnemyManager;
        SubLevel* subLevel;
        LevelGameplayManager gameplayManager;
        std::unique_ptr<LevelPlayerAnimationManager> animationManager;
        InputManager& inputManager;
    public:
        LevelPlayerManager(SubLevel* subLevel, InputManager& inputManager);
        void update();
        void addAnimation(unique_ptr<LevelPlayerAnimationManager> nextSceneManager);
};

class SubLevel {
        friend class Level;
        friend class EnemyManager;
        friend class ChangeSubLevelManager;
        friend class LevelGameplayManager;
        friend class LevelPlayerAnimationManager;
        Level* level;
        Character* player;
        std::shared_ptr<TileMap> background;
        std::shared_ptr<TileMap> blocks;
        std::shared_ptr<EnemyManager> enemies;
        std::shared_ptr<ChangeSubLevelManager> changeSubLevelManager;
        LevelPlayerManager playerManager;
        Camera2D* camera;
        std::string folderName;
        Vector2 initPlayerPosition;

        bool debug = false;
    public:
        SubLevel(Level* level, std::string folderName, Character* player, Vector2 initPlayerPosition, InputManager& inputManager, Camera2D* camera);
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
        std::string folderName;
    public:
        Level(std::string folderName);
        Level(std::string subLevelFolder, Vector2 playerPosition);
        void changeSubLevel(NextSubLevelScene nextScene);
        void draw(void);
        void update(void);
        void saveGame(std::string folderName);
        static vector<std::pair<std::string, std::string>> getSavedLevels();
        ~Level();
};