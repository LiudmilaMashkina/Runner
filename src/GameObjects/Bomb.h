#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>
#pragma warning(pop)

#include "IGameObject.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;
class ParticlesObject;

class Bomb : public IGameObject
{
public:
    Bomb(b2Body* body,
         GameWorld* world,
         const std::shared_ptr<ParticlesObject>& particles);
    virtual ~Bomb();

	virtual void update(float delta) override;
	
	b2Body* getBody() { return _body; }
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override { return GameObjectType::Bomb; }
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    
private:
	b2Body* _body = nullptr;
	cocos2d::Node* _node = nullptr;
	GameWorld* _world = nullptr;
    std::shared_ptr<ParticlesObject> _particles;
};

 
