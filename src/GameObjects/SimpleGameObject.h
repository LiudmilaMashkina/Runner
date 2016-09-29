#pragma once

#pragma warning(push, 0)
#include <Box2D/Box2D.h>
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
	
	b2Body* getBody() { return _body; }
    virtual b2Vec2 getPosition() override;

private:
	b2Body* _body = nullptr;
	cocos2d::Node* _node = nullptr;
	GameWorld* _world = nullptr;
};

 
