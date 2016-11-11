#include "DelayedDrop.h"
#include "GameObjects/IGameObject.h"

DelayedDrop::DelayedDrop(const std::shared_ptr<IGameObject>& object, float countdown) :
_object(object),
_countdown(countdown)
{}

void DelayedDrop::update(float delta)
{
    _countdown -= delta;
    
    if (_countdown <= 0.0f)
    {
        std::shared_ptr<IGameObject> strongPtr = _object.lock();
        if (strongPtr)
            strongPtr->drop();
    }
}

bool DelayedDrop::hasDropped() const
{
    if (_countdown < 0.0f)
        return true;
    return false;
}
