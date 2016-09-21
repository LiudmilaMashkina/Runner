#pragma warning(push, 0)

#pragma warning(pop)
#include "GameObjectComposer.h"
#include "GameObjectFactory.h"

USING_NS_CC;

GameObjectComposer::GameObjectComposer(GameWorld* world) :
_world(world)
{}

void GameObjectComposer::assembleLine(float minLength, b2Vec2 startPos)
{
	GameObjectFactory factory = GameObjectFactory(_world);

	float curLength = 0.0f;
	b2Vec2 elementSize(1, 1);

	while (curLength < minLength)
	{
		factory.createBox(b2Vec2(startPos.x + curLength, startPos.y), 0, elementSize, b2BodyType::b2_staticBody, "stone_basic_blue_1.png");
		curLength += elementSize.x;
	}
}
