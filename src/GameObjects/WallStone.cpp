#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "WallStone.h"
#include "WallController.h"
#include "GameWorld.h"
#include "Utils/Convert.h"
#include "Hero/Hero.h"

USING_NS_CC;

WallStone::WallStone(b2Body* body, cocos2d::Node* node, GameWorld* world, std::weak_ptr<WallController> wController) : SimpleGameObject::SimpleGameObject(body, node, world)
{
    _wController = wController;
    update(0);
}

WallStone::~WallStone()
{}

void WallStone::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    GameObjectType type = obj->getType();
    if (type == GameObjectType::Hero)
    {
        Hero* hero = dynamic_cast<Hero*>(obj.get());
        std::shared_ptr<WallController> strongPtr = _wController.lock();
        if (strongPtr && !strongPtr->getIsWallDestroyed())
        {
            if (hero->getState()->getStateId() == HeroStateId::Attack)
                strongPtr->destroyWall(obj->getPosition(), 10);
            else
            {
                strongPtr->destroyWall(obj->getPosition(), 1);
                static_cast<Hero*>(obj.get())->collideWall();
            }
        }
    }
}
