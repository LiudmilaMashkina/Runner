#include <memory>
#pragma once

#pragma warning(push, 0)
#include <Box2d/Box2D.h>
#pragma warning(pop)
#include "IGameObject.h"

namespace cocos2d { class Node; }
class b2Body;
class GameWorld;

class GameObjectComposer
{
public:
	GameObjectComposer(GameWorld* world);

	void assembleLine(float lineLength, b2Vec2 startPos);

private:
	GameWorld* _world = nullptr;
};

 