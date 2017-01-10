#pragma once

#pragma warning(push, 0)
#pragma warning(pop)

#include "SimpleGameObject.h"
#include "Utils/MacroCreate.h"
#include "AnimationEngine/IAnimation.h"

class GameWorld;

class Coin : public SimpleGameObject
{
public:
    CREATE_FUNC_4(Coin, b2Body*, body, cocos2d::Node*, node, GameWorld*, world, IAnimationPtr, animation);
    
    virtual ~Coin();
    
    virtual void update(float delta) override;
    virtual GameObjectType getType() const override { return GameObjectType::Coin; }
    
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    virtual bool isDroppable() override { return false; }
    
private:
    Coin(b2Body* body, cocos2d::Node* node, GameWorld* world, IAnimationPtr animation);
    
    IAnimationPtr _animation = nullptr;
};

 
