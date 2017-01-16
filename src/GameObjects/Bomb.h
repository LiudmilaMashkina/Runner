#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>
#pragma warning(pop)

#include "Utils/MacroCreate.h"
#include "SimpleGameObject.h"
#include "AnimationEngine/IAnimation.h"


namespace cocos2d { class Node; }
class b2Body;
class GameWorld;
class ParticlesObject;

class Bomb : public SimpleGameObject
{
public:
    CREATE_FUNC_5(Bomb, b2Body*, body, GameWorld*, world, cocos2d::Node*, node, IAnimationPtr, animation, const std::shared_ptr<ParticlesObject>&, particles);
    
    virtual ~Bomb();

	virtual void update(float delta) override;
	
	virtual GameObjectType getType() const override { return GameObjectType::Bomb; }
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    
    virtual void drop() override;
    
    //cocos2d::Node* getSprite() {return _node;}
    
private:
    Bomb(b2Body* body,
         GameWorld* world, cocos2d::Node* node, IAnimationPtr animation,
         const std::shared_ptr<ParticlesObject>& particles);
    void explode(const b2Vec2& pos);

	IAnimationPtr _animation = nullptr;
    std::shared_ptr<ParticlesObject> _particles;
};

 
