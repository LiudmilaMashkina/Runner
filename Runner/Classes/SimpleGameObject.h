#pragma once

#pragma warning(push, 0)

#pragma warning(pop)

#include "IGameObject.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;

class SimpleGameObject : public IGameObject
{
public:
	SimpleGameObject(b2Body* body, cocos2d::Node* node, GameWorld* world);
	~SimpleGameObject();

	virtual void update(float delta) override;

private:
	b2Body* _body = nullptr;
	cocos2d::Node* _node = nullptr;
	GameWorld* _world = nullptr;
};

 