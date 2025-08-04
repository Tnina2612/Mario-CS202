#pragma once
#include "core/Variables.hpp"
#include "raylib.h"
#include <unordered_map>
#include <string>

class MusicManager {
private:
    std::unordered_map<MusicType, Music> musicTracks;
    MusicType currentTrack;
    bool musicEnabled;
    float musicVolume;

    MusicManager();

public:
    MusicManager(const MusicManager&) = delete;
    void operator=(const MusicManager&) = delete;

    static MusicManager& getInstance();
    
    ~MusicManager();
    
    void loadMusic();
    void playMusic(MusicType musicType, bool loop = true);
    void stopMusic();
    void pauseMusic();
    void resumeMusic();
    void updateMusic();
    void setMusicVolume(float volume);
    void setMusicEnabled(bool enabled);
};