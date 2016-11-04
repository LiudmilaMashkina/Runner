#include <Box2D/Dynamics/Contacts/b2Contact.h>
#include "ContactListener.h"
#include "GameObjects/IGameObject.h"
#include "GameWorld.h"

ContactListener::ContactListener(GameWorld* world) :
_world(world)
{}

void ContactListener::BeginContact(b2Contact *contact)
{
    void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    IGameObject* objA = static_cast<IGameObject*>(bodyAUserData);
    
    bodyAUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    IGameObject* objB = static_cast<IGameObject*>(bodyAUserData);
    
    _world->addContact(objA, objB);
}

void ContactListener::EndContact(b2Contact *contact)
{

}
