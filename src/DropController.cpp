#include "DropController.h"
#include "GameWorld.h"
#include "GameObjects/IGameObject.h"
#include "Utils/Environment.h"

DropController::DropController(GameWorld* world) :
_world(world)
{}

DropController::~DropController()
{}

void DropController::update(float delta)
{
    for (DelayedDrop& drop : _drops)
        drop.update(delta);
    
    auto it = std::remove_if(_drops.begin(), _drops.end(), [](const DelayedDrop &drop)
                   {
                       return drop.hasDropped();
                   });
    _drops.erase(it, _drops.end());
    
    auto dropIf = [&](const std::shared_ptr<IGameObject>& object)
    {
        if (object->isDroppable())
        {
            if (object->getPosition().x >= _lastDropPoint &&
                object->getPosition().x <= _currentDropPoint)
            {
                float delay = Environment::generateFloatRand(0.1f, 1.0f);
                DelayedDrop d(object, delay);
                _drops.push_back(d);
            }
        }
        
    };    
    _world->forEach(dropIf);
    
    _lastDropPoint = _currentDropPoint;
}

void DropController::setDropPoint(float pointX)
{
    _currentDropPoint = pointX;
}
