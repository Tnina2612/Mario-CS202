#pragma once
#include <memory>
#include <raylib.h>
#include <level/Level.hpp>
#include "core/Scene.hpp"
#include "core/GameSession.hpp"
#include "ui/HUD.hpp"

class Program
{
private:
    bool running;
    Scene* currentScene;
    Scene* nextScene;
    Font font;
    GameSession session;
    HUD hud{&session};
    Image icon;

public:
    Program();
    ~Program();

    Program(const Program&) = delete;
    void operator=(const Program&) = delete;

    static Program& getInstance(); 
    void changeScene(Scene* scene);
    void run();

    Font getFont();
    GameSession& getSession();
    HUD& getHUD();
};