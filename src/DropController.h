#pragma once

#include <memory>
#include <vector>
#include "IUpdatable.h"
#include "Utils/MacroCreate.h"
#include "DelayedDrop.h"

class GameWorld;

class DropController : public IUpdatable
{
public:
    CREATE_FUNC_1(DropController, GameWorld*, world);
    ~DropController();
    
    virtual void update(float delta) override;
    
    void setDropPoint(float pointX);
    
private:
    DropController(GameWorld* world);
    
    std::vector<DelayedDrop> _drops;
    GameWorld* _world = nullptr;
    float _currentDropPoint = 0.0f;
    float _lastDropPoint = 0.0f;
};
