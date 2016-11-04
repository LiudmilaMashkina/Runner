#pragma once

class IUpdatable
{
public:
    virtual ~IUpdatable() {}
    
    virtual void update(float delta) = 0;

};
