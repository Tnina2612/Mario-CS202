#pragma once
#include<level/TileMap.hpp>
#include<entities/PlayerAnimation.hpp>
#include<block/Item/ItemAnimation.h>
#include<entities/Enemy/Enemy.hpp>
#include<entities/Enemy/EnemyFactory.hpp>
#include<raylib.h>
#include<iostream>
#include<entities/Character.hpp>
#include<entities/Mario.hpp>
#include<entities/Luigi.hpp>
#include<core/InputManager.hpp>
#include<core/Global.hpp>
#include<queue>
#include<entities/Enemy/Bowser.hpp>
#include<block/Item/MovingPlatform.h>
#include<block/Item/AnimationItem.h>

class Level;
class SubLevel;
class ItemManager;

class EnemyManager {
    std::vector<std::shared_ptr<Enemy>> list;
    std::queue<std::shared_ptr<Enemy>> spawnQueue;
    SubLevel* subLevel;
    std::vector<std::shared_ptr<Bowser>> listBowsers;

    // void rollBackFrames(Character* player, Enemy* enemy, Rectangle prevP);
    void checkCollisionsEnemyFireball(std::shared_ptr<Enemy> enemy, CharacterFireball* playerFireball);
    void checkCollisionsPlayerBowser(Character* player, Bowser* bowser);
    void checkCollisionsPlayerFireballBowser(Character* player, Bowser* bowser);
    void checkCollisionsFireballPlayerBowser(CharacterFireball* fire, Bowser* bowser);
    void processSpawnQueue();
public:
    EnemyManager(std::string filename, SubLevel* subLevel);
    void addEnemy(std::shared_ptr<Enemy> enemy);
    Vector2 getPlayerPos() const;
    void update();
    void updatePlayer();
    void draw() const;
    void saveToFile(std::string filename);
    Bowser * getBowser(void);
    ~EnemyManager(void) = default;
};

struct NextSubLevelScene {
    std::string filename;
    std::string worldType;
    Vector2 newPlayerPosition;
};

struct PlayerAnimationPoint {
    Rectangle detectRec;
    std::string key;
    std::vector<std::shared_ptr<PlayerAnimation>> animations;
    std::shared_ptr<NextSubLevelScene> nextScene;
};

class PlayerAnimationManager {
    std::vector<PlayerAnimationPoint> list;
    SubLevel* subLevel;
    std::queue<std::shared_ptr<PlayerAnimation>> todoAnimation;
    std::shared_ptr<NextSubLevelScene> toNextScene;
public:
    PlayerAnimationManager(std::string filename, SubLevel* subLevel);
    ~PlayerAnimationManager(void) = default;
    void update();
    void addAnimation(int id, ifstream& inp);
    bool okToChange(int id);
    void transit(int id);
    void draw() const;
    void saveToFile(std::string filename) const;
    bool inAnimation(void) const;
};

class PlayerGameplayManager {
    private:
        friend class EnemyManager;
        SubLevel* subLevel;
        Rectangle pastPlayerRec;
        // Rectangle pastPastPlayerRec;
    public:
        PlayerGameplayManager(SubLevel* subLevel);
        void update();
};

class PlayerManager {
    private:
        friend class EnemyManager;
        SubLevel* subLevel;
        PlayerGameplayManager gameplayManager;
        PlayerAnimationManager animationManager;
        InputManager& inputManager;
    public:
        PlayerManager(SubLevel* subLevel, InputManager& inputManager, std::string folderName);
        void update();
};

struct ItemAnimationPoint {
    AnimationItem* item;
    TileMap * blocks, * background;
    Bowser * bowser;
    Rectangle detectRec;
    std::string detectType;
    std::vector<std::shared_ptr<ItemAnimation>> animations;
    ItemAnimationPoint(AnimationItem* item = nullptr, TileMap * blocks = nullptr, TileMap * background = nullptr,
        Bowser * bowser = nullptr);
    void read(std::ifstream& inp, std::string filename);
    void saveToFile(std::ofstream& out);
};

class ItemAnimationManager {
    private:
        ItemManager* itemManager;
        std::queue<std::shared_ptr<ItemAnimation>> todoAnimation;
    public:
        ItemAnimationManager(ItemManager* itemManager);
        void draw(void) const;
        void update(void);
        bool inAnimation(void) const;
        bool isActivate(std::shared_ptr<ItemAnimationPoint> point);
};

class ItemManager {
        friend class ItemAnimationManager;
    private:
        SubLevel* subLevel;
        ItemAnimationManager animationManager;
        std::vector<std::shared_ptr<Item>> items;
        std::vector<std::shared_ptr<MovingPlatform>> movingPlatforms;
        std::vector<std::pair<std::shared_ptr<AnimationItem>, std::shared_ptr<ItemAnimationPoint>>> animationObjects;
    public:
        ItemManager(std::string filename, SubLevel* subLevel);
        void draw(void);
        void update();
        void addItem(std::shared_ptr<Item> item);
        void saveToFile(std::string filename);
};

class SubLevel {
        friend class Level;
        friend class TileMap;
        friend class EnemyManager;

        friend class PlayerAnimationManager;
        friend class PlayerGameplayManager;
        friend class PlayerManager;
        
        friend class ItemAnimationManager;
        friend class ItemManager;

        Level* level;
        Character* player;
        std::shared_ptr<TileMap> background;
        std::shared_ptr<TileMap> blocks;
        std::shared_ptr<EnemyManager> enemies;
        PlayerManager playerManager;
        ItemManager itemManager;
        Camera2D* camera;
        std::string folderName;
        Vector2 initPlayerPosition;

        bool debug = false;
        bool oke =false;
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
        static void switchTheme(std::string theme);
        static std::string getCurrentTheme();
        ~Level();
        std::shared_ptr<Character> getPlayer();
};