#pragma once

#include <SimpleAudioEngine.h>
#include "GameSoundType.h"

class AudioEngine // Singleton
{
public:
    void playMusic();
    void playSound(GameSoundType sound);
    
    static const std::unique_ptr<AudioEngine>& getInstace();
    
private:
    AudioEngine(){ AudioEngine::playMusic(); }
    
    static std::unique_ptr<AudioEngine> _audioEngine;
};
