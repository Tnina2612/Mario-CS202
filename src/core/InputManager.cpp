#include"../../include/core/InputManager.hpp"
#include<string>

void InputManager::addKey(KeyboardKey key) {
    // Initialize the key state if it doesn't exist
    if (keyStates.find(key) == keyStates.end()) {
        keyStates[key] = {false, false}; // Default to not pressed
    }
}

InputManager::~InputManager() {
    // Clean up listeners
    for(auto listener : listeners) {
        delete listener;
    }
    listeners.clear();
}

void InputManager::addListener(InputListener* listener) {
    if(find(listeners.begin(), listeners.end(), listener) != listeners.end()) {
        return; // Listener already exists
    }
    listeners.push_back(listener);
}



void InputManager::removeListener(InputListener* listener) {
    auto it = remove(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end()) {
        listeners.erase(it, listeners.end());
    }
}

void InputManager::addCharacter(Character* c) {
    character = c;
}

void InputManager::update() {
    if(keyStates.empty()) return;
    for(auto& [key, state] : keyStates) {
        bool isDown = IsKeyDown(key);
        if(isDown != state.second) {
            state.second = isDown;
        }
        if(isDown && !state.first && (key == KEY_LEFT || key == KEY_RIGHT)) {
            if(key == KEY_LEFT) {
                if(keyStates[KEY_RIGHT].first == false) {
                    keyStates[key].first = true; // Reset KEY_RIGHT if KEY_LEFT is pressed
                }
            }
            else if(key == KEY_RIGHT) {
                if(keyStates[KEY_LEFT].first == false) {
                    keyStates[key].first = true; // Reset KEY_LEFT if KEY_RIGHT is pressed
                }
            }
        }
        if(key != KEY_LEFT && key != KEY_RIGHT) {
            state.first = IsKeyPressed(key);;
        }
        if(!IsKeyDown(key)) {
            state = {false, false}; // Reset the key pressed state if the key is not down
        }
    }
    if(IsKeyPressed(KEY_LEFT)) {
        if(keyStates[KEY_RIGHT].first) {
            keyStates[KEY_RIGHT].first = false;
        }
        keyStates[KEY_LEFT].first = true; // Set KEY_LEFT as pressed
    }
    if(IsKeyPressed(KEY_RIGHT)) {
        if(keyStates[KEY_LEFT].first) {
            keyStates[KEY_LEFT].first = false;
        }
        keyStates[KEY_RIGHT].first = true; // Set KEY_RIGHT as pressed
    }
    if(IsKeyDown(KEY_LEFT)) {
        if(keyStates[KEY_RIGHT].first == false && keyStates[KEY_RIGHT].second == false) {
            keyStates[KEY_LEFT].first = true; // Set KEY_LEFT as down
        }
    }
    if(IsKeyDown(KEY_RIGHT)) {
        if(keyStates[KEY_LEFT].first == false && keyStates[KEY_LEFT].second == false) {
            keyStates[KEY_RIGHT].first = true; // Set KEY_RIGHT as down
        }
    }
    if(!IsKeyDown(KEY_LEFT) && !IsKeyDown(KEY_RIGHT) && !IsKeyDown(KEY_DOWN) && character->getBehavior() != JUMP) {
        character->setBehavior(IDLE); // Set character behavior to IDLE if no keys are pressed
        character->setVelocityX(0.0f); // Reset horizontal velocity
    }
    vector<KeyboardKey> keys = {KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN};

    // cout keys and their states
    for(auto key : keys) {
        if(keyStates.find(key) != keyStates.end() && key == keys[2]) {
            // cout << "Key: " << key  << ", Pressed: " << keyStates[key].first << ", Down: " << keyStates[key].second << endl;
        }
    }
    for(auto [key, state] : keyStates) {
        for(auto listener : listeners) {
            listener->onkey(key, state.first, state.second, character);
        }
    }
}

void upListener::onkey(KeyboardKey key, bool pressed, bool down, Character* character) {
    if(character == nullptr || key != KEY_UP) return;
    if(pressed && character->getOnGround()) {
        character->setBehavior(JUMP);
        character->setOnGround(false); // Set onGround to false when jumping
        character->setVeclocityY(-character->getJumpVelocity()); // Set initial jump velocity
    }
}

void downListener::onkey(KeyboardKey key, bool pressed, bool down, Character* character) {
    if(character == nullptr || key != KEY_DOWN) return;
    if(down && character->getOnGround()) {
        character->setBehavior(DUCK);
        character->setVelocityX(0.0f); // Stop horizontal movement when ducking
    }
}

void leftListener::onkey(KeyboardKey key, bool pressed, bool down, Character* character) {
    if(character == nullptr || key != KEY_LEFT) return;
    if(character->getBehavior() == BRAKE) return;
    if(pressed) {
        if(character->getOrientation() == RIGHT && character->getBehavior() == MOVE) {
            character->setBehavior(BRAKE);
        }
        else if(character->getOnGround() && character->getBehavior() != BRAKE) {
            character->setBehavior(MOVE);
            character->setOrientation(LEFT); // Change orientation to LEFT when moving left
        }
        else if(character->getOnGround() == false) {
            character->moveLeft();
        }
    }
}

void rightListener::onkey(KeyboardKey key, bool pressed, bool down, Character* character) {
    if(character == nullptr || key != KEY_RIGHT) return;
    if(character->getBehavior() == BRAKE) return;
    if(pressed) {
        if(character->getOrientation() == LEFT && character->getBehavior() == MOVE) {
            character->setBehavior(BRAKE);
        }
        else if(character->getOnGround() && character->getBehavior() != BRAKE) {
            character->setBehavior(MOVE);
            character->setOrientation(RIGHT); // Change orientation to RIGHT when moving right
        }
        else if(character->getOnGround() == false) {
            character->moveRight();
        }
    }
}