#pragma warning(push, 0)
#include <base/CCDirector.h>
#pragma warning(pop)
#include "Environment.h"

USING_NS_CC;

b2Vec2 Environment::getScreenSize()
{
	Size winSize = Director::getInstance()->getWinSize();
	b2Vec2 ptmWinSize;
	ptmWinSize.x = winSize.width / getPTMratio();
	ptmWinSize.y = winSize.height / getPTMratio();
	return ptmWinSize;
}

float32 Environment::getPTMratio()
{
	Size winSize = Director::getInstance()->getWinSize();
	float32 ptmWidth = winSize.width / 15;
	float32 ptmHeight = winSize.height / 10;

	if (ptmWidth > ptmHeight)
		return ptmHeight;
	else
		return ptmWidth;
}

