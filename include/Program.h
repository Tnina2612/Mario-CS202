#pragma once
#include<memory>
#include<stack>
#include<raylib.h>
#include<level/Level.hpp>
#include<iostream>

class Program
{
private:
    bool running;
    std::shared_ptr<Level> level;
    RenderTexture2D renderTexture;

public:
    Program();
    ~Program();

    void run();
};