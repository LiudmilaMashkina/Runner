#include "SceneManager.h"
#include "GameWorld.h"
#include "MainMenuScene.h"
#include "TestScene.h"
#include "SceneBuilder.h"
#include "GenericScene.h"

USING_NS_CC;

SceneManager* SceneManager::_manager = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (!_manager)
        SceneManager::_manager = new SceneManager();
    
    return _manager;
}

void SceneManager::startGame()
{
	auto scene = MainMenuScene::create();
	setScene(scene);
}

void SceneManager::showGameScene()
{
    GenericScene* scene = SceneBuilder()
    .withGameWorld()
    .withBackground()
    .withParticleLayer()
    .withLevelGenerator()
    .withHero()
    .withCamera()
    .build();
    
    setScene(scene);
}

void SceneManager::setScene(cocos2d::Scene* scene)
{
	if (_scene == nullptr)
		cocos2d::Director::getInstance()->runWithScene(scene);
	else
		cocos2d::Director::getInstance()->replaceScene(scene);

	_scene = scene;
}
