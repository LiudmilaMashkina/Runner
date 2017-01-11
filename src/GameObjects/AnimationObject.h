#pragma once

#include "IGameObject.h"
#include "AnimationEngine/IAnimation.h"
#include "Utils/StrongPtr.h"

class GameWorld;

class AnimationObject : public IGameObject
{
public:
    AnimationObject(GameWorld* world,
                    const cocos2d::Vector<cocos2d::SpriteFrame*> &frames,
                    int fps,
                    bool cycled);
    virtual ~AnimationObject();

    virtual void update(float delta) override;
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override;
    virtual b2Body* getBody() override { return nullptr; }
    virtual void setPosition(const b2Vec2& pos);
    
    StrongPtr<cocos2d::Sprite> getSprite() { return _sprite; }

private:
    IAnimationPtr _animation = nullptr;
    StrongPtr<cocos2d::Sprite> _sprite;
    GameWorld* _world = nullptr;
};

 
