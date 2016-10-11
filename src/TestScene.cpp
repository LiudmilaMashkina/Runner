#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#pragma warning(pop)
#include "TestScene.h"
#include "GameWorld.h"
#include "Utils/Environment.h"
#include "Utils/Convert.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"
#include "GameObjects/GameObjectComposer.h"
#include "GameObjects/GameLevelGenerator.h"
#include "GameCamera.h"

USING_NS_CC;

bool TestScene::init()
{
	if (!Scene::init())
		return false;

    _winSize = Environment::getScreenSize();
    
    auto background = createBackground("resources/background_1_1024x1024.jpg");
    addChild(background);

    Node* gameNode = Node::create();
    addChild(gameNode);
    
	_world = std::shared_ptr<GameWorld>(new GameWorld(b2Vec2(0, -10), gameNode));
    _generator = std::shared_ptr<GameLevelGenerator>(new GameLevelGenerator(_world.get()));
    
    std::vector<GameCamera::LayerInfo> layers;
    
    GameCamera::LayerInfo gameLayer;
    gameLayer.layer = gameNode;
    gameLayer.speedFactor = 1.0f;
    gameLayer.zoomFactor = 1.0f;
    layers.push_back(gameLayer);
    
    GameCamera::LayerInfo backgroundLayer;
    backgroundLayer.layer = background;
    backgroundLayer.speedFactor = 0.5f;
    backgroundLayer.zoomFactor = 0.5f;
    backgroundLayer.clamp = true;
    layers.push_back(backgroundLayer);
    
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

Sprite* TestScene::createBackground(const std::string & backgroundName)
{
    auto background = Sprite::create(backgroundName);
    
    Vec2 backgroundScale;
    backgroundScale.x = Convert::toPixels(_winSize.x) * 2 / background->getContentSize().width;
    backgroundScale.y = Convert::toPixels(_winSize.y) * 2/ background->getContentSize().height;
    background->setScale(backgroundScale.x, backgroundScale.y);
    background->setAnchorPoint(Vec2(0, 0));
    
    return background;
}

