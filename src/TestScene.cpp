#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#pragma warning(pop)
#include "TestScene.h"
#include "GameWorld.h"
#include "Utils/Environment.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"
#include "GameObjects/GameObjectComposer.h"

USING_NS_CC;

bool TestScene::init()
{
	if (!Scene::init())
		return false;

	_world = std::shared_ptr<GameWorld>(new GameWorld(b2Vec2(0, -10), this));

	b2Vec2 winSize = Environment::getScreenSize();

	GameObjectComposer composer(_world.get());

	GameObjectComposer::LineDef line;
	line.blocks.push_back(GameObjectComposer::LineDef::Block("stone_line_blue_0.png", 0.5f));
	line.blocks.push_back(GameObjectComposer::LineDef::Block("stone_line_blue_1.png", 0.75f));
	line.blocks.push_back(GameObjectComposer::LineDef::Block("stone_line_blue_2.png", 1.0f));
	line.blocks.push_back(GameObjectComposer::LineDef::Block("stone_line_blue_3.png", 2.0f));
	line.blocks.push_back(GameObjectComposer::LineDef::Block("stone_line_blue_4.png", 1.5f));
	line.blocks.push_back(GameObjectComposer::LineDef::Block("stone_line_blue_5.png", 0.5f));
	line.blocks.push_back(GameObjectComposer::LineDef::Block("stone_line_blue_6.png", 0.5f));
	line.length = 50;
	line.maxOverlap = 0;
	line.startPos.Set(winSize.x / 5, winSize.y * 0.75f);

	//composer.assembleLine(line);

	GameObjectComposer::BridgeDef bridge;
	bridge.startPos.Set(winSize.x / 5, winSize.y * 0.75f);
	bridge.direction.Set(1.0f, -0.1f);
	bridge.linkCount = 20;
	bridge.linkSize.Set(0.6f, 0.6f);
	bridge.overlap = 0.14f;

	composer.assembleBridge(bridge);

	auto physDebugDraw = B2DebugDrawLayer::create(_world->getPhysics(), Environment::getPTMratio());
	addChild(physDebugDraw, 100);

	scheduleUpdate();
	return true;
}

void TestScene::update(float delta)
{
	_world->update(delta);
}
