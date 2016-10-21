#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <2d/CCSpriteFrame.h>
#pragma warning(pop)

#include "Animation.h"

Animation::Animation(const cocos2d::Vector<cocos2d::SpriteFrame*> &frames,
                     int fps,
                     bool cycled) :
_frames(frames),
_interval(1.0/fps),
_cycled(cycled)
{
    reset();
}

Animation::~Animation()
{}

void Animation::update(float delta)
{
    _timeLeft -= delta;
    
    if (_timeLeft <= 0)
    {
        setNextFrame();
        _timeLeft += _interval;
    }
}

bool Animation::setNextFrame()
{
    if (_currentFrameIndex < _frames.size() - 1)
    {
        ++_currentFrameIndex;
        _sprite->setSpriteFrame(_frames.at(_currentFrameIndex));

        return true;
    }
    
    if (_cycled)
    {
        _currentFrameIndex = 0;
        _sprite->setSpriteFrame(_frames.at(_currentFrameIndex));
        return true;
    }
    else
        return false;
}

bool Animation::isFinished() const
{
    if (_cycled)
        return false;
    else
        if (_currentFrameIndex == _frames.size() - 1)
            return true;
        else
            return false;
}

void Animation::reset()
{
    _timeLeft = _interval;
    _currentFrameIndex = 0;
    
    if (_sprite)
        _sprite->setSpriteFrame(_frames.at(_currentFrameIndex));
}

FrameId Animation::getCurrentFrameId() const
{
    return FrameId(this, _currentFrameIndex);
}

void Animation::setTarget(cocos2d::Sprite *sprite)
{
    _sprite = sprite;
}






