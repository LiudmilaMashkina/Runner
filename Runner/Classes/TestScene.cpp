#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#pragma warning(pop)
#include "TestScene.h"
#include "GameWorld.h"
#include "GameObjectFactory.h"
#include "Environment.h"
#include "B2DebugDrawLayer.h"

USING_NS_CC;

bool TestScene::init()
{
	if (!Scene::init())
		return false;

	_world = std::shared_ptr<GameWorld>(new GameWorld(b2Vec2(0, -10), this));

	b2Vec2 winSize = Environment::getScreenSize();

	GameObjectFactory factory(_world.get());
	factory.createBox(b2Vec2(winSize.x / 2, winSize.y / 2 - 2));
	factory.createCircle(b2Vec2(winSize.x / 2, winSize.y / 2 + 2));

	auto physDebugDraw = B2DebugDrawLayer::create(_world->getPhysics(), Environment::getPTMratio());
	addChild(physDebugDraw, 100);

	scheduleUpdate();
	return true;
}

void TestScene::update(float delta)
{
	_world->update(delta);
}
