#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <Box2D/Box2D.h>
#pragma warning(pop)
#include "GroundStone.h"
#include "GameWorld.h"
#include "Utils/Convert.h"
#include "ParticlesObject.h"

USING_NS_CC;

GroundStone::GroundStone(b2Body* body,
                         GameWorld* world,
                         cocos2d::Node* node,
                         const std::shared_ptr<ParticlesObject>& particles) :
SimpleGameObject::SimpleGameObject(body, node, world),
_particles(particles)
{
	update(0);
}

GroundStone::~GroundStone()
{}

void GroundStone::update(float delta)
{
    b2Vec2 bodyPos = _body->GetPosition();
    float bodyAngle = _body->GetAngle();
    
    _node->setPosition(Convert::toPixels(bodyPos));
    _node->setRotation(Convert::toDegrees(-bodyAngle));
    
    std::shared_ptr<ParticlesObject> strongPtr = _particles.lock();
    assert(strongPtr);
    strongPtr->setPosition(bodyPos);
}

void GroundStone::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    if (obj->getType() != GameObjectType::Hero)
        return;
    
    std::shared_ptr<ParticlesObject> strongPtr = _particles.lock();
    strongPtr->setPaused(false);
}
