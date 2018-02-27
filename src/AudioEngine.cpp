#include <map>
#include <string>
#include "AudioEngine.h"

using namespace std;

namespace
{
    map<GameSoundType, string> soundMap = {
        {GameSoundType::Bomb, "rsrc/bomb.mp3"},
        {GameSoundType::Button, "rsrc/click1.mp3"},
        {GameSoundType::Coin, "rsrc/coin.mp3"},
        {GameSoundType::Fire, "rsrc/flame.mp3"}
    };
    
    const string musicFileName = "rsrc/main_theme.mp3";
}

std::unique_ptr<AudioEngine> AudioEngine::_audioEngine;

void AudioEngine::playMusic()
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playBackgroundMusic(musicFileName.c_str(), true);
}

void AudioEngine::stopMusic()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

void AudioEngine::preloadMusic()
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic(musicFileName.c_str());
}

void AudioEngine::playSound(GameSoundType sound)
{
    auto it = soundMap.find(sound);
    
    if (it != soundMap.end())
    {
        string soundName = it->second;
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->preloadEffect(soundName.c_str());
        audio->playEffect(soundName.c_str());
    }
}

unsigned int AudioEngine::playLoopedSound(GameSoundType sound)
{
    auto it = soundMap.find(sound);
    unsigned int soundId = 0;
    if (it != soundMap.end())
    {
        string soundName = it->second;
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        soundId = audio->playEffect(soundName.c_str(), true);
    }
    
    return soundId;
}

void AudioEngine::preloadSounds()
{
    auto it = soundMap.begin();
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    while (it != soundMap.end())
        audio->preloadEffect(it->second.c_str());
}

void AudioEngine::stopSound(unsigned int soundId)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(soundId);
}

const unique_ptr<AudioEngine>& AudioEngine::getInstance()
{
    if (_audioEngine == nullptr)
    {
        unique_ptr<AudioEngine> audioEngine(new AudioEngine());
        _audioEngine = move(audioEngine);
    }
    
    return _audioEngine;
}
