#pragma once

#include <functional>
#include <memory>
#include "Utils/MacroCreate.h"
#include "IUpdatable.h"

class UpdaterFunc : public IUpdatable
{
public:
    CREATE_FUNC_1(UpdaterFunc, const std::function<void(float)> &, delegate);
    
    virtual void update(float delta) override;
  
private:
    UpdaterFunc(const std::function<void(float)> &delegate);
    
    std::function<void(float)> _delegate;
};
