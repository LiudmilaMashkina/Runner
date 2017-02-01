//
//  IAnimation.h
//  Wanderer
//
//  Created by Luda on 04/12/15.
//
//

#ifndef Wanderer_IAnimation_h
#define Wanderer_IAnimation_h

#include "FrameId.h"
#include "IUpdatable.h"

namespace cocos2d
{
    class Sprite;
}

class IAnimation : public IUpdatable
{
public:
    virtual ~IAnimation() {}
    
    virtual void update(float delta) = 0;
    virtual bool isFinished() const = 0;
    virtual void reset() = 0;
    virtual FrameId getCurrentFrameId() const = 0;
    virtual void setTarget(cocos2d::Sprite *sprite) = 0;
};

#endif
