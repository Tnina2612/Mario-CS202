#include<entities/Animation.hpp>
#include<iostream>

AnimationVectorTextureFlyweight::AnimationVectorTextureFlyweight() : textures(0)
{
}

AnimationVectorTextureFlyweight::AnimationVectorTextureFlyweight(std::vector<std::string> filenames) {
    for(std::string& s : filenames) {
        textures.push_back(Texture(LoadTexture(s.c_str())));
        if(textures.back().id == 0) {
            __throw_runtime_error(("Cannot load texture: " + s).c_str());
        } 
    }
}

void AnimationVectorTextureFlyweight::draw(int posX, int posY, int id) {
    if(id < 0 || id >= textures.size()) __throw_runtime_error("ID is out of bound.");
    DrawTexture(textures[id], posX, posY, WHITE);
}

AnimationVectorTextureFlyweight::~AnimationVectorTextureFlyweight() {
    for(Texture2D& t : textures) {
        UnloadTexture(t);
    }
}

std::unordered_map<std::string, AnimationVectorTextureFlyweight> AnimationVectorTextureFlyweightFactory::storage;

AnimationVectorTextureFlyweight* AnimationVectorTextureFlyweightFactory::getFlyweight(std::string name) {
    string folderName = "./assets/images/levels";
    if(LevelVar::ThemeID == LevelVar::Overworld) {
        folderName += "/overworld/";
    } else if(LevelVar::ThemeID == LevelVar::Underground) {
        folderName += "/underground/";
    }

    string storedName = name + to_string(LevelVar::ThemeID);
    if(storage.find(storedName) == storage.end()) {
        std::vector<std::string> filenames;
        filenames = {name};
        for(std::string& name : filenames) {
            name = folderName + name + ".png";
        }
        storage.emplace(storedName, filenames);
    }

    return &storage[storedName];
}

AnimationVectorTexture::AnimationVectorTexture(std::string name) :
    flyweight(AnimationVectorTextureFlyweightFactory::getFlyweight(name))
{
    // Constructor
}

void AnimationVectorTexture::draw(float posX, float posY) {
    flyweight->draw(posX, posY, currentTexture);
}

void AnimationVectorTexture::update() {
    elaspedTime += GetFrameTime();
    if(elaspedTime >= textureTime) {
        currentTexture++;
        if(currentTexture < startID || currentTexture > endID) {
            currentTexture = startID;
        }
    }
}

void AnimationVectorTexture::setTextureRange(int startID, int endID) {
    this->startID = startID;
    this->endID = endID;
    currentTexture = startID;
}