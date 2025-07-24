#pragma once
#include "raylib.h"
#include <vector>
#include <unordered_map>
#include <algorithm>
#include "Singleton.h"
#include "../entities/Character.hpp"

using namespace std;


class InputListener {
public:
    virtual void onkey(KeyboardKey key, bool pressed, bool down, Character* Character) = 0;
    virtual ~InputListener() {}
};

class upListener : public InputListener {
public:
    void onkey(KeyboardKey key, bool pressed, bool down, Character* character) override;
};

class downListener : public InputListener {
public:
    void onkey(KeyboardKey key, bool pressed, bool down, Character* character) override;
};

class leftListener : public InputListener {
public: 
    void onkey(KeyboardKey key, bool pressed, bool down, Character* character) override;
};

class rightListener : public InputListener {
public:
    void onkey(KeyboardKey key, bool pressed, bool down, Character* character) override;
};


class InputManager {
    template<class T>
    friend class Singleton;

public:
    void addKey(KeyboardKey key);
    void addListener(InputListener* listener);
    void removeListener(InputListener* listener);
    void update();
    void addCharacter(Character* character);
    
    ~InputManager() = default;
private:
    unordered_map<KeyboardKey, pair<bool, bool>> keyStates;
    vector<InputListener*> listeners;
    Character* character = nullptr;

    InputManager() = default;
    InputManager(const InputManager& other) = delete;
    InputManager& operator = (const InputManager& other) = delete;
};