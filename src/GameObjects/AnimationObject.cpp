#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#pragma warning(pop)

#include "AnimationObject.h"
#include "AnimationEngine/Animation.h"
#include "Utils/Convert.h"
#include "GameWorld.h"


AnimationObject::AnimationObject(GameWorld* world,
                                 const cocos2d::Vector<cocos2d::SpriteFrame*> &frames,
                                 int fps,
                                 bool cycled) :
_world(world)
{
    assert(!frames.empty());
    _animation = std::shared_ptr<Animation>(new Animation(frames, fps, cycled));
    
    _sprite = cocos2d::Sprite::createWithSpriteFrame(frames.at(0));
    
    assert(_sprite);
    _animation->setTarget(_sprite);
    _world->getGraphics()->addChild(_sprite); 
}

AnimationObject::~AnimationObject()
{
    _sprite->removeFromParentAndCleanup(true);
}

void AnimationObject::update(float delta)
{
    if (_animation->isFinished())
    {
        _world->removeObjectLater(this);
        return;
    }
    _animation->update(delta);
}

b2Vec2 AnimationObject::getPosition()
{
    return Convert::toMeters(_sprite->getPosition());
}

GameObjectType AnimationObject::getType() const
{
    return GameObjectType::Animation;
}

void AnimationObject::setPosition(const b2Vec2 &pos)
{
    _sprite->setPosition(Convert::toPixels(pos));
}
