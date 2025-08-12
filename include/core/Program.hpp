#pragma once
#include <memory>
#include <raylib.h>
#include <level/Level.hpp>
#include "core/Scene.hpp"
#include "core/GameSession.hpp"
#include "ui/HUD.hpp"
#include <stack>

class Program
{
private:
    bool running;
    Scene* nextScene;
    Font font;
    GameSession session;
    HUD* hud;
    Image icon;
    std::stack<Scene*> sceneStack;

    // Singleton Design Pattern
    Program();

public:
    Program(const Program&) = delete;
    void operator=(const Program&) = delete;

    ~Program();

    static Program& getInstance(); 
    void pushScene(Scene* scene);
    void popScene();
    void run();

    Font getFont();
    GameSession& getSession();
    HUD& getHUD();
};