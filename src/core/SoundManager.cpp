#include "core/SoundManager.hpp"

SoundManager::SoundManager() : soundEnabled(true), masterVolume(0.5f) {

}

SoundManager& SoundManager::getInstance() {
    static SoundManager instance; // Created once, destroyed automatically and safely
    return instance;
}

SoundManager::~SoundManager() {
    for (auto& pair : sounds) {
        UnloadSound(pair.second);
    }
    sounds.clear();
}

void SoundManager::loadSounds() {
    // Load all sound effects
    sounds[SoundType::COIN] = LoadSound("assets/sounds/smb_coin.wav");
    sounds[SoundType::JUMP_SMALL] = LoadSound("assets/sounds/smb_jump-small.wav");
    sounds[SoundType::JUMP_SUPER] = LoadSound("assets/sounds/smb_jump-super.wav");
    sounds[SoundType::POWERUP] = LoadSound("assets/sounds/smb_powerup.wav");
    sounds[SoundType::POWERDOWN] = LoadSound("assets/sounds/smb_pipe.wav");
    sounds[SoundType::BUMP] = LoadSound("assets/sounds/smb_bump.wav");
    sounds[SoundType::BREAKBLOCK] = LoadSound("assets/sounds/smb_breakblock.wav");
    sounds[SoundType::FIREBALL] = LoadSound("assets/sounds/smb_fireball.wav");
    sounds[SoundType::STOMP] = LoadSound("assets/sounds/smb_stomp.wav");
    sounds[SoundType::KICK] = LoadSound("assets/sounds/smb_kick.wav");
    sounds[SoundType::ONE_UP] = LoadSound("assets/sounds/smb_1-up.wav");
    sounds[SoundType::FLAGPOLE] = LoadSound("assets/sounds/smb_flagpole.wav");
    sounds[SoundType::BOWSER_FIRE] = LoadSound("assets/sounds/smb_bowserfire.wav");
    sounds[SoundType::BOWSER_FALLS] = LoadSound("assets/sounds/smb_bowserfalls.wav");
    sounds[SoundType::FIREWORKS] = LoadSound("assets/sounds/smb_fireworks.wav");
    sounds[SoundType::PIPE] = LoadSound("assets/sounds/smb_pipe.wav");
    sounds[SoundType::VINE] = LoadSound("assets/sounds/smb_vine.wav");
    sounds[SoundType::WARNING] = LoadSound("assets/sounds/smb_warning.wav");
    sounds[SoundType::MARIO_DIE] = LoadSound("assets/sounds/smb_mariodie.wav");
    sounds[SoundType::GAMEOVER] = LoadSound("assets/sounds/smb_gameover.wav");
    sounds[SoundType::STAGE_CLEAR] = LoadSound("assets/sounds/smb_stage_clear.wav");
    sounds[SoundType::WORLD_CLEAR] = LoadSound("assets/sounds/smb_world_clear.wav");

    // Set initial volume for all sounds
    for (auto& pair : sounds) {
        SetSoundVolume(pair.second, masterVolume);
    }
}

void SoundManager::playSound(SoundType soundType) {
    if (!soundEnabled) return;

    auto it = sounds.find(soundType);
    if (it != sounds.end()) {
        PlaySound(it->second);
    }
}

void SoundManager::setSoundEnabled(bool enabled) {
    soundEnabled = enabled;
}

void SoundManager::setMasterVolume(float volume) {
    masterVolume = volume;
    for (auto& pair : sounds) {
        SetSoundVolume(pair.second, masterVolume);
    }
}

bool SoundManager::isSoundEnabled() const {
    return soundEnabled;
}