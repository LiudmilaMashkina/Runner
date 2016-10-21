//
//  FrameId.h
//  Wanderer
//
//  Created by Luda on 07/12/15.
//
//

#ifndef Wanderer_FrameId_h
#define Wanderer_FrameId_h
#include "Utils/Forwards.h"

FORWARD_DECLARE_SHARED(IAnimation)

struct FrameId
{
    FrameId(const IAnimation* animation = nullptr, int frame = -1) :
    animation(animation),
    frame(frame)
    {}
    
    bool operator<(const FrameId &other) const
    {
        if (animation == other.animation)
            return frame < other.frame;
        
        return animation < other.animation;
    }
    
    const IAnimation* animation;
    const int frame;
};

#endif
