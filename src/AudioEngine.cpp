#include <map>
#include <string>
#include "AudioEngine.h"

using namespace std;

namespace
{
    std::map<GameSoundType, string> soundMap = {
        {GameSoundType::Bomb, "rsrc/bomb.mp3"}
    };
    
    const string musicFileName = "rsrc/main_theme.mp3";
}

std::unique_ptr<AudioEngine> AudioEngine::_audioEngine;

void AudioEngine::playMusic()
{
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic(musicFileName.c_str());
    audio->playBackgroundMusic(musicFileName.c_str(), true);
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

const unique_ptr<AudioEngine>& AudioEngine::getInstace()
{
    if (_audioEngine == nullptr)
    {
        unique_ptr<AudioEngine> audioEngine(new AudioEngine());
        _audioEngine = move(audioEngine);
    }
    
    return _audioEngine;
}
