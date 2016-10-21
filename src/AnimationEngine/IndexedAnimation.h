//
//  IndexedAnimation.h
//  Wanderer
//
//  Created by Luda on 09/12/15.
//
//

#ifndef __Wanderer__IndexedAnimation__
#define __Wanderer__IndexedAnimation__

#include "IAnimation.h"

class IndexedAnimation : public IAnimation
{
public:
    IndexedAnimation(IAnimation *inner, int indexShift);
    virtual ~IndexedAnimation();
    
    virtual void update(float delta) override;
    virtual bool isFinished() const override;
    virtual void reset() override;
    virtual FrameId getCurrentFrameId() const override;
    
private:
    IAnimation *_inner = nullptr;
    int _indexShift = 0;
};

#endif /* defined(__Wanderer__IndexedAnimation__) */
