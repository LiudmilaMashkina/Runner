#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#include <Box2d/Box2D.h>
#pragma warning(pop)
#include "LightingStone.h"
#include "GameWorld.h"
#include "Utils/Convert.h"

USING_NS_CC;

LightingStone::LightingStone(b2Body* body,
                             cocos2d::Node* node,
                             cocos2d::Node* lighting,
                             GameWorld* world) :
_body(body),
_node(node),
_lighting(lighting),
_world(world)
{
	update(0);
}

LightingStone::~LightingStone()
{
	_node->removeFromParentAndCleanup(true);
	_world->getPhysics()->DestroyBody(_body);
}

void LightingStone::update(float delta)
{
	b2Vec2 bodyPos = _body->GetPosition();
	float bodyAngle = _body->GetAngle();

	_node->setPosition(Convert::toPixels(bodyPos));
	_node->setRotation(Convert::toDegrees(-bodyAngle));
    
    if (_isTouched == true)
    {
        _timer += 10;
        if (_timer >= 0)
        {
            float curOpacity = _lighting->getOpacity();
            float lightDelta = 255 - curOpacity;
            float opacity = curOpacity + lightDelta / 16;
            _lighting->setOpacity(opacity);
        }
    }
}

b2Vec2 LightingStone::getPosition()
{
    return _body->GetPosition();
}

void LightingStone::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    if (obj->getType() != GameObjectType::Hero)
        return;
    
    _isTouched = true;
}

void LightingStone::drop()
{
    _body->SetType(b2BodyType::b2_dynamicBody);
    _body->SetLinearDamping(0.1f);
    _body->SetAngularDamping(0.1f);
}
