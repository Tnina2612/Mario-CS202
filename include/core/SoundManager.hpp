#pragma once
#include "core/Variables.hpp"
#include <unordered_map>

class SoundManager {
private:
    std::unordered_map<SoundType, Sound> sounds;
    bool soundEnabled;
    float masterVolume;

    SoundManager();

public:
    SoundManager(const SoundManager&) = delete;
    void operator=(const SoundManager&) = delete;

    static SoundManager& getInstance();

    ~SoundManager();
    
    void loadSounds();
    void playSound(SoundType soundType);
    void setSoundEnabled(bool enabled);
    void setMasterVolume(float volume);
    bool isSoundEnabled() const;
};