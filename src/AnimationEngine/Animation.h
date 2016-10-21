#pragma once

#include "IAnimation.h"
#include "base/CCVector.h"

namespace cocos2d
{
    class Sprite;
    class SpriteFrame;
}

class Animation : public IAnimation
{
public:
    Animation(const cocos2d::Vector<cocos2d::SpriteFrame*> &frames,
              int fps,
              bool cycled);
    
    virtual ~Animation();
    
    virtual void update(float delta) override;
    virtual bool isFinished() const override;
    virtual void reset() override;
    virtual FrameId getCurrentFrameId() const override;
    virtual void setTarget(cocos2d::Sprite *sprite) override;

  
private:
    bool setNextFrame();
    
    cocos2d::Sprite* _sprite = nullptr;
    cocos2d::Vector<cocos2d::SpriteFrame*> _frames;
    const float _interval = 0;
    bool _cycled = false;
    float _timeLeft = 0;
    int _currentFrameIndex = 0;
};
