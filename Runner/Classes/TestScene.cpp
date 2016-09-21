#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#pragma warning(pop)
#include "TestScene.h"
#include "GameWorld.h"
#include "GameObjects/GameObjectFactory.h"
#include "Utils/Environment.h"
#include "DebugDraw/B2DebugDrawLayer.h"
#include "GameObjects/GameObjectComposer.h"

USING_NS_CC;

bool TestScene::init()
{
	if (!Scene::init())
		return false;

	_world = std::shared_ptr<GameWorld>(new GameWorld(b2Vec2(0, -10), this));

	b2Vec2 winSize = Environment::getScreenSize();

	GameObjectComposer composer(_world.get());
	composer.assembleLine(5.3f, b2Vec2(winSize.x / 4, winSize.y / 2 - 2));

	GameObjectFactory factory(_world.get());
	factory.createCircle(b2Vec2(winSize.x / 2, winSize.y / 2 + 2), 0, 2, b2BodyType::b2_dynamicBody, "stone_basic_blue_3.png");

	auto physDebugDraw = B2DebugDrawLayer::create(_world->getPhysics(), Environment::getPTMratio());
	addChild(physDebugDraw, 100);

	scheduleUpdate();
	return true;
}

void TestScene::update(float delta)
{
	_world->update(delta);
}
