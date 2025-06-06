#pragma once

#include "Program.h"
// #include "Pages/LinkedListPage.h"
// #include "Pages/HashTablePage.h"
// #include "Pages/AVLTreePage.h"
// #include "Pages/GraphPage.h"


// Lớp MainPage
class MainPage : public Page {
private:
    Program* program;

    // Button soundButton;

    // Texture2D dayButtonTexture;

public:
    MainPage(Program* prog);
    ~MainPage();

    void handleInput() override;
    
    void update(float deltaTime) override;

    void draw() override;
};