#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "WallStone.h"
#include "WallController.h"
#include "GameWorld.h"
#include "Utils/Convert.h"
#include "Hero/Hero.h"

USING_NS_CC;

WallStone::WallStone(b2Body* body, cocos2d::Node* node, GameWorld* world, std::weak_ptr<WallController> wController) :
_body(body),
_node(node),
_world(world),
_wController(wController)
{
    update(0);
}

WallStone::~WallStone()
{
    _node->removeFromParentAndCleanup(true);
    _world->getPhysics()->DestroyBody(_body);
}

void WallStone::update(float delta)
{
    b2Vec2 bodyPos = _body->GetPosition();
    float bodyAngle = _body->GetAngle();
    
    _node->setPosition(Convert::toPixels(bodyPos));
    _node->setRotation(Convert::toDegrees(-bodyAngle));
}

b2Vec2 WallStone::getPosition()
{
    return _body->GetPosition();
}

void WallStone::drop()
{
    _body->SetType(b2BodyType::b2_dynamicBody);
    _body->SetLinearDamping(0.1f);
    _body->SetAngularDamping(0.1f);
}

void WallStone::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    GameObjectType type = obj->getType();
    if (type == GameObjectType::Hero)
    {
        Hero* hero = dynamic_cast<Hero*>(obj.get());
        std::shared_ptr<WallController> strongPtr = _wController.lock();
        if (strongPtr)
        {
            if (hero->getState()->getStateId() == HeroStateId::Attack)
                strongPtr->destroyWall(obj->getPosition(), 10);
            else
                strongPtr->destroyWall(obj->getPosition(), 1);
        }
    }
}
