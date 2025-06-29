#pragma once
#include<memory>
#include<stack>
#include<Pages/Page.h>
#include<raylib.h>
#include<level/Level.hpp>
#include<iostream>

class Program
{
private:
    std::stack<std::unique_ptr<Page>> pages;
    bool running;
    std::shared_ptr<Level> level;
    RenderTexture2D renderTexture;

public:
    Program();
    ~Program();

    void run();

    void pushPage(std::unique_ptr<Page> page);
    void popPage();
    bool isEmpty() const;
};