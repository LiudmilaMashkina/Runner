#include "Button.h"
#include "2d/CCSprite.h"
#include "gui/BorderdNode.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"

namespace gui
{
	Button::Button(cocos2d::Node* node, const std::string &normal, const std::string &pressed)
	{
		cocos2d::Sprite* normalSprite = cocos2d::Sprite::create(normal);
		normalSprite->setAnchorPoint(Vec2(0, 0));
		normalSprite->setVisible(true);
		_normal = normalSprite;

		cocos2d::Sprite* pressedSprite = cocos2d::Sprite::create(pressed);
		pressedSprite->setAnchorPoint(Vec2(0, 0));
		pressedSprite->setVisible(false);
		_pressed = pressedSprite;

		node->setContentSize(normalSprite->getContentSize());
		node->addChild(normalSprite);
		node->addChild(pressedSprite);

		auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(Button::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);
		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, node);

		setNode(node);
	}
    
    void Button::setEnabled(bool enabled)
    {
        _enabled = enabled;
    }

	bool Button::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
	{
        if (!_enabled)
            return false;
        
		Vec2 touchPos =	getNode()->convertTouchToNodeSpace(touch);

		cocos2d::Vec2 size = getSize();
		if (touchPos.x < 0 || touchPos.x > size.x || touchPos.y < 0 || touchPos.y > size.y)
			return false;

		if (getNode()->isVisible() == false)
			return false;

		_normal->setVisible(false);
		_pressed->setVisible(true);

		event->stopPropagation();
		return true;
	}

	void Button::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
	{
	}

	void Button::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
	{
		_normal->setVisible(true);
		_pressed->setVisible(false);
		_callback(this);
	}


	Button::~Button()
	{
	}

	std::shared_ptr<Button> Button::create(const std::string &normal, const std::string &pressed)
	{
		auto node = BorderdNode::create();
		return std::shared_ptr<Button>(new Button(node, normal, pressed));
	}
	
	void Button::setCallback(const std::function<void(Button*)> callback)
	{
		_callback = callback;
	}

}
