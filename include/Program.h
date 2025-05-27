#pragma once

#include <memory>
#include <stack>
#include "Pages/Page.h"
#include "raylib.h"

class Program
{
private:
    std::stack<std::unique_ptr<Page>> pages;
    bool running;

public:
    Program();
    ~Program();

    void run();

    void pushPage(std::unique_ptr<Page> page);
    void popPage();
    bool isEmpty() const;
};