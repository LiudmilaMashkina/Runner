#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#pragma warning(pop)
#include <set>
#include <math.h>
#include "Bulb.h"
#include "GameWorld.h"
#include "Utils/Convert.h"

USING_NS_CC;

Bulb::Bulb(b2Body* body,
           GameWorld* world,
           Node* node) :
_body(body),
_world(world),
_node(node)
{
	update(0);
}

Bulb::~Bulb()
{
	_node->removeFromParentAndCleanup(true);
	_world->getPhysics()->DestroyBody(_body);
}

void Bulb::update(float delta)
{
	b2Vec2 bodyPos = _body->GetPosition();
	float bodyAngle = _body->GetAngle();

	_node->setPosition(Convert::toPixels(bodyPos));
	_node->setRotation(Convert::toDegrees(-bodyAngle));
    
    float curOpacity = _node->getOpacity();
    float lightDelta = _targetOpacity - curOpacity;
    _node->setOpacity(curOpacity + lightDelta / 8);
}

b2Vec2 Bulb::getPosition()
{
    return Convert::toMeters(_node->getPosition());
}

void Bulb::drop()
{
    _targetOpacity = 255.0f;
}

void Bulb::lightOn(bool switchedOn)
{
    if (switchedOn == false)
        _node->setOpacity(0.0f);
    else if (switchedOn == true)
        _node->setOpacity(255.0f);
}
