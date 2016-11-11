#pragma once
#include <memory>

class IGameObject;

class DelayedDrop
{
public:
    DelayedDrop(const std::shared_ptr<IGameObject>& object, float countdown);
    
    void update(float delta);
    bool hasDropped() const;
    
private:
    std::weak_ptr<IGameObject> _object;
    float _countdown = 0.0f;
};
