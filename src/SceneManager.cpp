#include "SceneManager.h"
#include "GameWorld.h"
#include "MainMenuScene.h"
#include "TestScene.h"
#include "GameScene.h"
#include "GenericScene.h"

USING_NS_CC;

SceneManager* SceneManager::_manager = nullptr;

SceneManager* SceneManager::getInstance()
{
    if (!_manager)
        SceneManager::_manager = new SceneManager();
    
    return _manager;
}

void SceneManager::showMainMenu()
{
	auto scene = MainMenuScene::create();
	setScene(scene);
}

void SceneManager::showGameScene()
{
    GameScene* gameScene = GameScene::create();
    
    setScene(gameScene);
}

void SceneManager::setScene(cocos2d::Scene* scene)
{
	if (_scene == nullptr)
		cocos2d::Director::getInstance()->runWithScene(scene);
	else
    {
        auto transition = TransitionFade::create(0.5, scene, Color3B::BLACK);
		cocos2d::Director::getInstance()->replaceScene(transition);
    }

	_scene = scene;
}
