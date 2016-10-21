//
//  IndexedAnimation.cpp
//  Wanderer
//
//  Created by Luda on 09/12/15.
//
//

#include "IndexedAnimation.h"

IndexedAnimation::IndexedAnimation(IAnimation *inner, int indexShift) :
_inner(inner),
_indexShift(indexShift)
{
    
}

IndexedAnimation::~IndexedAnimation()
{
    delete _inner;
}

void IndexedAnimation::update(float delta)
{
    _inner->update(delta);
}

bool IndexedAnimation::isFinished() const
{
    return _inner->isFinished();
}

void IndexedAnimation::reset()
{
    _inner->reset();
}

FrameId IndexedAnimation::getCurrentFrameId() const
{
    FrameId frameId = _inner->getCurrentFrameId();
    return FrameId(frameId.animation, frameId.frame + _indexShift);
}

