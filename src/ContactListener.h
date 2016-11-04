#pragma once

#include <Box2d/Dynamics/b2WorldCallbacks.h>

class GameWorld;

class ContactListener : public b2ContactListener
{
public:
    ContactListener(GameWorld* world);
    
    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;
    
private:
    GameWorld* _world = nullptr;
};
