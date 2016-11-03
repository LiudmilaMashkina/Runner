#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#pragma warning(pop)
#include "Bomb.h"
#include "GameWorld.h"
#include "Utils/Convert.h"

USING_NS_CC;

Bomb::Bomb(b2Body* body, GameWorld* world) :
_body(body),
_world(world)
{
    _node = Sprite::create("resources/bomb.png");
    _world->getGraphics()->addChild(_node);
    
	update(0);
}

Bomb::~Bomb()
{
	_node->removeFromParentAndCleanup(true);
	_world->getPhysics()->DestroyBody(_body);
}

void Bomb::update(float delta)
{
	b2Vec2 bodyPos = _body->GetPosition();
	float bodyAngle = _body->GetAngle();

	_node->setPosition(Convert::toPixels(bodyPos));
	_node->setRotation(Convert::toDegrees(-bodyAngle));
}

b2Vec2 Bomb::getPosition()
{
    return Convert::toMeters(_node->getPosition());
}
