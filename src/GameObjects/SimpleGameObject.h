#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>

#pragma warning(pop)

#include "IGameObject.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;

class SimpleGameObject : public IGameObject
{
public:
	SimpleGameObject(b2Body* body, cocos2d::Node* node, GameWorld* world);
	virtual ~SimpleGameObject();

	virtual void update(float delta) override;
	
	virtual b2Body* getBody() override { return _body; }
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override { return GameObjectType::SimpleGameObject; }
    virtual void drop() override;
    virtual bool isDroppable() override { return true; }
    
private:
	b2Body* _body = nullptr;
	cocos2d::Node* _node = nullptr;
	GameWorld* _world = nullptr;
};

 
