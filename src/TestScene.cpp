#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#pragma warning(pop)
#include "TestScene.h"
#include "GameWorld.h"
#include "Utils/Environment.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"
#include "GameObjects/GameObjectComposer.h"
#include "GameObjects/GameLevelGenerator.h"
#include "GameCamera.h"

USING_NS_CC;

bool TestScene::init()
{
	if (!Scene::init())
		return false;

    Node* gameNode = Node::create();
    addChild(gameNode);
    
	_world = std::shared_ptr<GameWorld>(new GameWorld(b2Vec2(0, -10), gameNode));
    _winSize = Environment::getScreenSize();
    _generator = std::shared_ptr<GameLevelGenerator>(new GameLevelGenerator(_world.get()));
    
    std::vector<GameCamera::LayerInfo> layers;
    
    GameCamera::LayerInfo gameLayer;
    gameLayer.layer = gameNode;
    gameLayer.speedFactor = 1.0f;
    gameLayer.zoomFactor = 1.0f;
    layers.push_back(gameLayer);
    
    _camera = std::shared_ptr<GameCamera>(new GameCamera(layers));
    
	auto physDebugDraw = B2DebugDrawLayer::create(_world->getPhysics(), Environment::getPTMratio());
	gameNode->addChild(physDebugDraw, 100);

	scheduleUpdate();
	return true;
}

void TestScene::update(float delta)
{
    static float time = 0;
    time += delta;
    
	_world->update(delta);
    b2Vec2 camPos = {time * 2, 0};
    _camera->setPosition(b2Vec2(camPos));
    _generator->generateUntil(camPos.x + _winSize.x * 0.75f);
    
    auto shouldRemove = [&](const std::shared_ptr<IGameObject>& obj)
    {
        b2Vec2 objPos = obj->getPosition();
        if (objPos.x < camPos.x + 5)
            return true;
        return false;
    };
    
    _world->removeObject(shouldRemove);
}
