#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "FrameId.h"
#include "Utils/Forwards.h"

FORWARD_DECLARE_SHARED(IAnimation)

namespace cocos2d
{
    class Sprite;
}

class AnimationEngine
{
public:
    AnimationEngine();
    
    void addRule(const IAnimationPtr &fromAnimation,
                 const std::string &desiredGroupId,
                 const IAnimationPtr &transtionAnimation);
    
    void addFallback(const std::string &groupId, const IAnimationPtr &animation);
    
    void goToAnimationGroup(const std::string &groupId);
    void update(float delta);
    
    cocos2d::Sprite* start();
    
private:
    void setAnimation(const IAnimationPtr &animation);
  
    std::map<IAnimationPtr, std::map<std::string, IAnimationPtr>> _rules;
    std::map<std::string, IAnimationPtr> _fallbacks; //group id -> animation
    
    IAnimationPtr _currentAnimation = nullptr;
    cocos2d::Sprite *_sprite = nullptr;
};
