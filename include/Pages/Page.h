#pragma once

// The virtual class Page, for other screens inherited from it
class Page
{
public:
    virtual ~Page() {}

    // Pure virtual methods obligate derived classes to override it
    virtual void handleInput() = 0;
    virtual void update(float deltaTime) = 0;
    virtual void draw() = 0;
};