#include "2d/CCSprite.h"
#include "AnimationEngine.h"
#include "Animation.h"

using namespace std;

AnimationEngine::AnimationEngine()
{
    
}

void AnimationEngine::addRule(const IAnimationPtr &fromAnimation,
                              const std::string &desiredGroupId,
                              const IAnimationPtr &transtionAnimation)
{
    assert(fromAnimation);
    _rules[fromAnimation][desiredGroupId] = transtionAnimation;
}

void AnimationEngine::addFallback(const std::string &groupId, const IAnimationPtr &animation)
{
    _fallbacks[groupId] = animation;
}

void AnimationEngine::goToAnimationGroup(const std::string &groupId)
{
    IAnimationPtr nextAnimation;
    
    if (_currentAnimation)
    {
        auto ruleIt = _rules.find(_currentAnimation);
        if (ruleIt != _rules.end())
        {
            const map<string, IAnimationPtr> &transitions = ruleIt->second;
            auto transitionIt = transitions.find(groupId);
            if (transitionIt != transitions.end())
                nextAnimation = transitionIt->second;
        }
    }
    
    if (!nextAnimation)
    {
        auto it = _fallbacks.find(groupId);
        assert(it != _fallbacks.end());
        nextAnimation = it->second;
    }

    setAnimation(nextAnimation);
}

void AnimationEngine::update(float delta)
{
    assert(_sprite);
    
    if (!_currentAnimation)
        return;
    
    _currentAnimation->update(delta);
    if (_currentAnimation->isFinished())
    {
        auto ruleIt = _rules.find(_currentAnimation);
        assert(ruleIt != _rules.end());
        const map<string, IAnimationPtr> &transitions = ruleIt->second;
        
        auto transitionIt = transitions.find("auto");
        assert(transitionIt != transitions.end());
        
        IAnimationPtr nextAnimation = transitionIt->second;
        setAnimation(nextAnimation);
    }
}

cocos2d::Sprite* AnimationEngine::start()
{
    if (!_sprite)
    {
        _sprite = cocos2d::Sprite::create("resources/jump_white_left_0.png");
        assert(_sprite);
    }
    return _sprite;
}

void AnimationEngine::setAnimation(const IAnimationPtr &animation)
{
    if (_currentAnimation)
        _currentAnimation->reset();
    
    animation->setTarget(_sprite);
    _currentAnimation = animation;
}
















