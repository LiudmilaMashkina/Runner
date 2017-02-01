#include "Button.h"
#include "2d/CCSprite.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"

namespace gui2
{
    USING_NS_CC;
    
    void Button::setOpacity(GLubyte opacity)
    {
        Node::setOpacity(opacity);
        _normal->setOpacity(opacity);
        _pressed->setOpacity(opacity);
    }
    
	bool Button::initWith(const std::string &normal, const std::string &pressed)
	{
        if (!Node::init())
            return false;
        
		Sprite* normalSprite = Sprite::create(normal);
		normalSprite->setAnchorPoint(Vec2(0, 0));
		normalSprite->setVisible(true);
		_normal = normalSprite;

		Sprite* pressedSprite = Sprite::create(pressed);
		pressedSprite->setAnchorPoint(Vec2(0, 0));
		pressedSprite->setVisible(false);
		_pressed = pressedSprite;

		setContentSize(normalSprite->getContentSize());
		addChild(normalSprite);
		addChild(pressedSprite);

		auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(Button::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(Button::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(Button::onTouchEnded, this);
		getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
        
        return true;
	}

	bool Button::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
	{
        if (!_enabled)
            return false;
        
		Vec2 touchPos =	convertTouchToNodeSpace(touch);

		cocos2d::Vec2 size = getContentSize();
		if (touchPos.x < 0 || touchPos.x > size.x || touchPos.y < 0 || touchPos.y > size.y)
			return false;

		if (isVisible() == false)
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
        if (_callback)
            _callback(this);
	}

	void Button::setCallback(const std::function<void(Button*)> callback)
	{
		_callback = callback;
	}

}
