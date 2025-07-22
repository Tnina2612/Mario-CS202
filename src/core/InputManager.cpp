#include"../../include/core/InputManager.hpp"

void InputManager::addKey(KeyboardKey key) {
    // Initialize the key state if it doesn't exist
    if (keyStates.find(key) == keyStates.end()) {
        keyStates[key] = false; // Default to not pressed
    }
}

void InputManager::addListener(Listener* listener) {
    listeners.push_back(listener);
}



void InputManager::removeListener(Listener* listener) {
    auto it = remove(listeners.begin(), listeners.end(), listener);
    if (it != listeners.end()) {
        listeners.erase(it, listeners.end());
    }
}

void InputManager::update() {
    if(keyStates.empty()) return;
    for(auto& [key, state] : keyStates) {
        bool isPressed = IsKeyPressed(key);
        if(isPressed == state) continue; // No change in key state
        for(auto listener : listeners) {
            if(listener) {
                listener->onkey(key, isPressed);
            }
        }
        state = isPressed; // Update the key state
    }
}