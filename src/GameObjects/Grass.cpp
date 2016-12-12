#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#pragma warning(pop)
#include <set>
#include <math.h>
#include "Grass.h"
#include "GameWorld.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/Environment.h"
#include "GameObjectFactory.h"
#include "ParticlesObject.h"

USING_NS_CC;

Grass::Grass(b2Body* body,
           GameWorld* world,
             Node* node,
             const std::weak_ptr<ParticlesObject>& particles) :
_body(body),
_world(world),
_node(node),
_particles(particles)
{
	update(0);
}

Grass::~Grass()
{
	_node->removeFromParentAndCleanup(true);
	_world->getPhysics()->DestroyBody(_body);
}

void Grass::update(float delta)
{
	b2Vec2 bodyPos = _body->GetPosition();
	float bodyAngle = _body->GetAngle();

	_node->setPosition(Convert::toPixels(bodyPos));
	_node->setRotation(Convert::toDegrees(-bodyAngle));
    
    std::shared_ptr<ParticlesObject> strongPtr = _particles.lock();
    assert(strongPtr);
    strongPtr->setPosition(bodyPos);
}

b2Vec2 Grass::getPosition()
{
    return Convert::toMeters(_node->getPosition());
}

void Grass::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    if (obj->getType() != GameObjectType::Hero)
        return;
    
    std::shared_ptr<ParticlesObject> strongPtr = _particles.lock();
    strongPtr->setPaused(false);
}
