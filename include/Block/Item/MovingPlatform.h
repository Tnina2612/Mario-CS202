#pragma once

#include<vector>
#include<unordered_map>
#include<memory>
#include"raylib.h"

#include"entities/Animation.hpp"



class MovingPlatformType {
public:
    Texture2D _texture;
    MovingPlatformType(const std::string& path = "./assets/images/sprite-sheets/items.png");
    virtual ~MovingPlatformType();
};

class MovingPlatform {
private:
    bool _isActive = false;

    Vector2 _startPos;      // Vị trí ban đầu
    Vector2 _endPos;        // Vị trí kết thúc
    Vector2 targetPos;

    Animation m_animation;
    std::vector<Rectangle> allFrames;
    std::shared_ptr<MovingPlatformType> _type;
    int sizeMovementType;

    Vector2 _pos;
    Vector2 _velocity;
    Vector2 _curVelocity;
    float _acceleration = 20.f;

    void move(float dt);
public:
    // PlatformSize size;     // Kích thước platform
    MovingPlatform();
    MovingPlatform(Vector2 startPos, Vector2 endPos);
    // MovingPlatform(Vector2 pos, float dist, float spd, MoveDirection dir, Texture2D tex, PlatformSize s);
    void setVelocity(Vector2 vel);
    void setType(std::shared_ptr<MovingPlatformType> type);
    void setAllFrames(std::vector<Rectangle> frames);
    void setAniFrames(std::vector<Rectangle> frames);
    void setActive(bool isActive);
    void update(float dt = GetFrameTime());
    void draw();
    Rectangle getRect() const; // Lấy hình chữ nhật va chạm
    void setSizeMovementType(int sizeMovementType);
    int getSizeMovementType() const;
    Vector2 getStartPos() const;
    Vector2 getEndPos() const;
};

class MovingPlatformFactory {
private:
    static std::shared_ptr<MovingPlatformType> s_platformTypes;
public:
    static std::shared_ptr<MovingPlatform> createPlatform(int type, Vector2 startPos, 
                                                            Vector2 endPos); //< 0: small vertical, 1: medium vertical, 2: large vertical, 3: small horizontal, 4: medium horizontal, 5: large horizontal
};
