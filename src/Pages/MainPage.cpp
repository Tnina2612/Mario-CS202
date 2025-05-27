#include "Pages/MainPage.h"

MainPage::MainPage(Program* prog)
    : program(prog)
{
}

MainPage::~MainPage()
{
}

void MainPage::handleInput() 
{
 
}

void MainPage::update(float deltaTime) 
{
  
}

void MainPage::draw() 
{
    BeginDrawing();
    DrawCircle(50, 50, 50, RED);
    EndDrawing();
}