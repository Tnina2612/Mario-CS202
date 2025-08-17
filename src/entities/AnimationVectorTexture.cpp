#include<entities/Animation.hpp>
#include<iostream>
#include <stdexcept>

AnimationVectorTextureFlyweight::AnimationVectorTextureFlyweight() : textures(0)
{
}

AnimationVectorTextureFlyweight::AnimationVectorTextureFlyweight(std::vector<std::string> filenames) {
    for(std::string& s : filenames) {
        if(s.find("invisible") != std::string::npos) {
            textures.push_back(Texture2D{0, 1, 1, 1, 0});
            continue;
        }
        textures.push_back(Texture(LoadTexture(s.c_str())));
        if(textures.back().id == 0) {
            throw runtime_error(("Cannot load texture: " + s).c_str());
        } 
    }
}

void AnimationVectorTextureFlyweight::draw(float posX, float posY, float rotation, int id) const {
    if(id < 0 || id >= textures.size()) throw runtime_error("ID is out of bound.");
    if(textures[id].id != 0) { 
        DrawTextureEx(textures[id], Vector2{posX, posY}, rotation, 1.f, WHITE);
    }
}

int AnimationVectorTextureFlyweight::getNumFrames() const {
    return textures.size();
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
    } else if(LevelVar::ThemeID == LevelVar::Castle) {
        folderName += "/castle/";
    }

    string storedName = name + to_string(LevelVar::ThemeID);
    if(storage.find(storedName) == storage.end()) {
        std::vector<std::string> filenames;

        if(name.find("question") == 0) {
            filenames = {"question1", "question2", "question3", "question1"};
        } else if(name.find("coin") == 0) {
            filenames = {"coin1", "coin2", "coin3", "coin1"};
        } else if(name.find("axe") == 0) {
            filenames = {"axe1", "axe2", "axe3"};
        } else {
            filenames = {name};
        }

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
    setTextureRange(0, flyweight->getNumFrames() - 1);
}

void AnimationVectorTexture::draw(float posX, float posY, float rotation) const {
    flyweight->draw(posX, posY, rotation, currentTexture);
}

void AnimationVectorTexture::update() {
    elapsedTime += GetFrameTime();
    if(elapsedTime >= textureTime) {
        elapsedTime = 0;
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