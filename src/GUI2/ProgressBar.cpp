#pragma warning(push, 0)
#include <2d/CCProgressTimer.h>
#pragma warning(pop)

#include "ProgressBar.h"

USING_NS_CC;

namespace gui2
{
	bool ProgressBar::initWith(const std::string &base, const std::string &progress)
	{
        if (!Node::init())
            return false;
        
		cocos2d::Sprite* baseSprite = cocos2d::Sprite::create(base);
		baseSprite->setAnchorPoint(Vec2(0, 0));
		_base = baseSprite;
        addChild(baseSprite);

        auto size = baseSprite->getContentSize();
        
        _progress = ProgressTimer::create(Sprite::create(progress));
        _progress->setAnchorPoint(Vec2(0.5, 0.5));
        _progress->setType(ProgressTimer::Type::BAR);
        _progress->setMidpoint(Vec2(0, 1));
        _progress->setBarChangeRate(Vec2(1, 0));
        _progress->setPercentage(0);
        _progress->setPosition(size.width / 2, size.height / 2);
        addChild(_progress);
    
		setContentSize(size);
        
        return true;
	}

	ProgressBar::~ProgressBar()
	{
	}

    void ProgressBar::setProgress(int percents)
    {
        _progress->setPercentage(percents);
    }
    
    void ProgressBar::setProgressColor(const cocos2d::Color3B &color)
    {
        _progress->setColor(color);
    }
}
