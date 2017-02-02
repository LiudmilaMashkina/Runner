#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#include <Box2d/Box2D.h>
#pragma warning(pop)
#include "LightingStone.h"
#include "GameWorld.h"
#include "Utils/Convert.h"
#include "ParticlesObject.h"

USING_NS_CC;

LightingStone::LightingStone(b2Body* body,
                             cocos2d::Node* node,
                             cocos2d::Node* lighting,
                             const std::shared_ptr<ParticlesObject>& particles,
                             GameWorld* world) : SimpleGameObject::SimpleGameObject(body, node, world),
_body(body),
_node(node),
_lighting(lighting)
{
	update(0);
}

LightingStone::~LightingStone()
{}

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

void LightingStone::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    if (obj->getType() != GameObjectType::Hero)
        return;
    
    _isTouched = true;
}
