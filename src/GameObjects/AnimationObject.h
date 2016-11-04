#pragma once

#include "IGameObject.h"
#include "AnimationEngine/IAnimation.h"

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
    
    void setPosition(const b2Vec2& pos);
    
private:
    IAnimationPtr _animation = nullptr;
    cocos2d::Sprite* _sprite = nullptr;
    GameWorld* _world = nullptr;
};

 
