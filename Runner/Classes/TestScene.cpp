#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#pragma warning(pop)
#include "TestScene.h"

USING_NS_CC;

bool TestScene::init()
{
	if (!Scene::init())
		return false;

	auto sprite = Sprite::create("stone_basic_blue_1.png");
	addChild(sprite);

	Size winSize = Director::getInstance()->getWinSize();

	sprite->setPosition(winSize.width / 2, winSize.height / 2);

	return true;
}
