#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <2d/CCProgressTimer.h>
#include <2d/CCScene.h>
#pragma warning(pop)

#include "ProgressBar.h"
#include "GUI/BorderdNode.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"

USING_NS_CC;

namespace gui
{
	ProgressBar::ProgressBar(cocos2d::Node* node, const std::string &base, const std::string &progress)
	{
		cocos2d::Sprite* baseSprite = cocos2d::Sprite::create(base);
		baseSprite->setAnchorPoint(Vec2(0, 0));
		//baseSprite->setVisible(true);
		_base = baseSprite;
        node->addChild(baseSprite);

        _progress = ProgressTimer::create(Sprite::create(progress));
        if (_progress != NULL)
        {
            _progress->setAnchorPoint(Vec2(0, 0));
            _progress->setType(ProgressTimer::Type::BAR);
            _progress->setMidpoint(Vec2(0, 1));
            _progress->setBarChangeRate(Vec2(1, 0));
            _progress->setPercentage(30);
            _progress->setPosition(Vec2(0, 0));
            node->addChild(_progress);
        }

		node->setContentSize(baseSprite->getContentSize());

        setNode(node);
	}

	ProgressBar::~ProgressBar()
	{
	}

	std::shared_ptr<ProgressBar> ProgressBar::create(const std::string &base, const std::string &progress)
	{
		auto node = BorderdNode::create();
		return std::shared_ptr<ProgressBar>(new ProgressBar(node, base, progress));
	}
    
    void ProgressBar::setLifes(int lifes)
    {
        _progress->setPercentage(lifes);
    }
}
