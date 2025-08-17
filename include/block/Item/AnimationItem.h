#pragma once
#include<entities/Animation.hpp>
#include<fstream>
#include<iostream>
#include<string>

class AnimationItem {
    private:
        Vector2 pos;
        AnimationVectorTexture animation;
        std::string name;
        bool vanish_ = false;
    public:
        AnimationItem(std::string name, Vector2 pos);
        void update();
        void draw() const;
        void setPosition(Vector2 newPos);
        Vector2 getPosition(void) const;
        void saveToFile(std::ofstream& out) const;
        void vanish(void);
        bool isVanishing(void) const;
};