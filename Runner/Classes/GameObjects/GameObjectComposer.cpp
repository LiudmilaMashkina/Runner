#pragma warning(push, 0)
#include <base/CCDirector.h>
#include <renderer/CCTextureCache.h>
#pragma warning(pop)
#include "GameObjectComposer.h"
#include "GameObjectFactory.h"
#include "SimpleGameObject.h"
#include "Utils/Environment.h"
#include "Utils/Convert.h"

USING_NS_CC;

GameObjectComposer::GameObjectComposer(GameWorld* world) :
_world(world)
{}

void GameObjectComposer::assembleLine(const LineDef& def)
{
	GameObjectFactory factory = GameObjectFactory(_world);

	for (float curLength = 0.0f; curLength < def.length; )
	{
		int num = Environment::generateIntRand(0, def.blocks.size() - 1);
		const LineDef::Block& block = def.blocks[num];
		
		b2Vec2 leftCorner(def.startPos.x + curLength, def.startPos.y);
		factory.createStaticStone(leftCorner, block.width, block.textureName);
		curLength += block.width;
	}
}

void GameObjectComposer::assembleBridge(const BridgeDef & def)
{
	GameObjectFactory factory = GameObjectFactory(_world);

	b2Vec2 dir = def.direction;
	dir.Normalize();

	float angle = atan2f(dir.y, dir.x);

	b2Body* prev = nullptr;
	for (int i = 0; i < def.linkCount; ++i)
	{
		b2BodyType bodyType = i == 0 || i == def.linkCount - 1 ? b2BodyType::b2_staticBody : b2BodyType::b2_dynamicBody;

		float dist = 0.5f * def.linkSize.x + (1 - def.overlap) * i * def.linkSize.x;
		b2Vec2 pos = def.startPos + dist * dir;
		auto curObj = factory.createBox(pos, angle, def.linkSize, bodyType, "hanging_bridge_0.png");
		b2Body* curBody = curObj->getBody();

		if (prev)
		{
			b2RevoluteJointDef jointDef;
			jointDef.bodyA = prev;
			jointDef.localAnchorA.Set(def.linkSize.x * 0.45f, 0.0f);
			jointDef.bodyB = curBody;
			jointDef.localAnchorB.Set(-def.linkSize.x * 0.45f, 0.0f);
			_world->getPhysics()->CreateJoint(&jointDef);
		}
		prev = curBody;
	}
}

