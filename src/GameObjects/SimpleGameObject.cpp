#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <Box2D/Box2D.h>
#pragma warning(pop)
#include "SimpleGameObject.h"
#include "GameWorld.h"
#include "Utils/Convert.h"

USING_NS_CC;

SimpleGameObject::SimpleGameObject(b2Body* body, Node* node, GameWorld* world) :
_body(body),
_node(node),
_world(world)
{
	update(0);
}

SimpleGameObject::~SimpleGameObject()
{
	_node->removeFromParentAndCleanup(true);
	_world->getPhysics()->DestroyBody(_body);
}

void SimpleGameObject::update(float delta)
{
	b2Vec2 bodyPos = _body->GetPosition();
	float bodyAngle = _body->GetAngle();

	_node->setPosition(Convert::toPixels(bodyPos));
	_node->setRotation(Convert::toDegrees(-bodyAngle));
}

b2Vec2 SimpleGameObject::getPosition()
{
    return _body->GetPosition();
}

void SimpleGameObject::drop()
{
    _body->SetType(b2BodyType::b2_dynamicBody);
    _body->SetLinearDamping(0.1f);
    _body->SetAngularDamping(0.1f);
}
