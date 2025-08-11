#pragma once
#include<vector>
#include<raylib.h>
#include<string>
#include<unordered_map>

class AnimationVectorTextureFlyweight {
private:
    std::vector<Texture2D> textures;
public:
    AnimationVectorTextureFlyweight();
    AnimationVectorTextureFlyweight(std::vector<std::string> filenames);
    void draw(float posX, float posY, float rotation, int id);
    int getNumFrames() const;
    ~AnimationVectorTextureFlyweight();
};

class AnimationVectorTextureFlyweightFactory {
private:
    static std::unordered_map<std::string, AnimationVectorTextureFlyweight> storage;
public:
    AnimationVectorTextureFlyweightFactory() = default;
    static AnimationVectorTextureFlyweight* getFlyweight(std::string name);
};