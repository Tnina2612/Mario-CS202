#include "core/MusicManager.hpp"

MusicManager::MusicManager() : musicEnabled(true), musicVolume(0.5f) {

}

MusicManager& MusicManager::getInstance() {
    static MusicManager instance; // Created once, destroyed automatically and safely
    return instance;
}

MusicManager::~MusicManager() {
    // Stop current music before unloading
    stopMusic();

    for (auto& pair : musicTracks) {
        UnloadMusicStream(pair.second);
    }
    musicTracks.clear();
}

void MusicManager::loadMusic() {
    musicTracks[MusicType::OVERWORLD] = LoadMusicStream("assets/music/01-main-theme-overworld.wav");
    musicTracks[MusicType::UNDERGROUND] = LoadMusicStream("assets/music/02-underworld.wav");
    musicTracks[MusicType::UNDERWATER] = LoadMusicStream("assets/music/03-underwater.wav");
    musicTracks[MusicType::CASTLE] = LoadMusicStream("assets/music/04-castle.wav");

    // Set initial volume for all sounds
    for (auto& pair : musicTracks) {
        SetMusicVolume(pair.second, musicVolume);
    }
}

void MusicManager::playMusic(MusicType musicType, bool loop) {
    if (!musicEnabled) return;

    stopMusic();

    auto it = musicTracks.find(musicType);
    if (it != musicTracks.end()) {
        currentTrack = musicType;
        it->second.looping = loop;
        PlayMusicStream(it->second);
    }
}

void MusicManager::stopMusic() {
    if (!musicTracks.empty()) {
        StopMusicStream(musicTracks[currentTrack]);
    }
}

void MusicManager::pauseMusic() {
    if (!musicTracks.empty()) {
        PauseMusicStream(musicTracks[currentTrack]);
    }
}

void MusicManager::resumeMusic() {
    if (!musicTracks.empty()) {
        ResumeMusicStream(musicTracks[currentTrack]);
    }
}

void MusicManager::updateMusic() {
    if (!musicTracks.empty() && musicEnabled) {
        UpdateMusicStream(musicTracks[currentTrack]);
    }
}

void MusicManager::setMusicVolume(float volume) {
    musicVolume = volume;
    for (auto& pair : musicTracks) {
        SetMusicVolume(pair.second, musicVolume);
    }
}

void MusicManager::setMusicEnabled(bool enabled) {
    musicEnabled = enabled;
    if (!enabled) {
        // Stop music when disabled
        stopMusic();
    }
}