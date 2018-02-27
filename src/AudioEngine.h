#pragma once

#include <SimpleAudioEngine.h>
#include "GameSoundType.h"

class AudioEngine // Singleton
{
public:
    void playMusic();
    void stopMusic();
    void preloadMusic();
    
    void playSound(GameSoundType sound);
    unsigned int playLoopedSound(GameSoundType sound);
    void preloadSounds();
    void stopSound(unsigned int soundId);
    
    static const std::unique_ptr<AudioEngine>& getInstance();
    
private:
    AudioEngine(){}
    
    static std::unique_ptr<AudioEngine> _audioEngine;
};
