#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "Coin.h"
#include "../AudioEngine.h"
#include "../GameSoundType.h"
#include "WallController.h"
#include "GameWorld.h"
#include "Utils/Convert.h"
#include "Hero/Hero.h"
#include "AnimationEngine/Animation.h"

USING_NS_CC;

Coin::Coin(b2Body* body, cocos2d::Node* node, GameWorld* world, IAnimationPtr animation) : SimpleGameObject::SimpleGameObject(body, node, world),
_animation(animation)
{
    update(0);
}

Coin::~Coin()
{}

void Coin::update(float delta)
{
    /*
    if (_animation->isFinished())
    {
        _world->removeObjectLater(this);
        return;
    }
    */
    _animation->update(delta);
}

void Coin::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    if (obj->getType() != GameObjectType::Hero)
        return;
    
    AudioEngine::getInstance()->playSound(GameSoundType::Coin);
    static_cast<Hero*>(obj.get())->collectCoin();
    _world->removeObjectLater(this);
}
