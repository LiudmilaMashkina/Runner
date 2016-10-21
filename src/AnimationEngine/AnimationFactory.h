//
//  AnimationFactory.h
//  Wanderer
//
//  Created by Luda on 05/12/15.
//
//

#ifndef __Wanderer__AnimationFactory__
#define __Wanderer__AnimationFactory__

#include <map>
#include "Utils/Forwards.h"
#include "IAnimation.h"

FORWARD_DECLARE_SHARED(IAnimation)
FORWARD_DECLARE_SHARED(AnimationEngine)

class AnimationFactory
{
public:
    AnimationEnginePtr getHeroAnimationEngine();
    AnimationEnginePtr getEngine(const std::string &fileName);
    
private:
    IAnimationPtr getAnimation(const std::string &prefix,
                               int startFrame,
                               int endFrame,
                               int fps,
                               bool isCycled);
    
    std::string getFileName(const std::string &fileName, int i) const;
    std::map<std::string, IAnimationPtr> getAnimationsFromJson(const std::string &fileName);
    

};

#endif /* defined(__Wanderer__AnimationFactory__) */
