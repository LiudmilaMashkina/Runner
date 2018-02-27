#include "CheckBox.h"
#include "GUI/BorderdNode.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"
#include "../GameSoundType.h"
#include "../AudioEngine.h"

USING_NS_CC;

namespace gui2
{
    void CheckBox::setOpacity(GLubyte opacity)
    {
        Node::setOpacity(opacity);
        _normal->setOpacity(opacity);
        _checked->setOpacity(opacity);
    }
    
	bool CheckBox::initWith(const std::string &normal, const std::string &checked, bool condition)
	{
        if (!Node::init())
            return false;
        
		cocos2d::Sprite* normalSprite = cocos2d::Sprite::create(normal);
		normalSprite->setAnchorPoint(Vec2(0, 0));
		_normal = normalSprite;

		cocos2d::Sprite* checkedSprite = cocos2d::Sprite::create(checked);
		checkedSprite->setAnchorPoint(Vec2(0, 0));
		_checked = checkedSprite;
        
        if (condition)
        {
            normalSprite->setVisible(true);
            checkedSprite->setVisible(false);
        }
        else
        {
            normalSprite->setVisible(false);
            checkedSprite->setVisible(true);
        }

		setContentSize(normalSprite->getContentSize());
		addChild(normalSprite);
		addChild(checkedSprite);

		auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(CheckBox::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(CheckBox::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(CheckBox::onTouchEnded, this);
		getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

        return true;
	}

	bool CheckBox::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
	{
        if (!_enabled)
            return false;
        
		Vec2 touchPos =	convertTouchToNodeSpace(touch);

		cocos2d::Vec2 size = getContentSize();
		if (touchPos.x < 0 || touchPos.x > size.x || touchPos.y < 0 || touchPos.y > size.y)
			return false;

		if (isVisible() == false)
			return false;
        
        AudioEngine::getInstance()->playSound(GameSoundType::Button);
        
        if (_isChecked == false)
        {
            _normal->setVisible(false);
            _checked->setVisible(true);
            _isChecked = true;
            setCallback(_callbackOff);
        }
        else
        {
            _normal->setVisible(true);
            _checked->setVisible(false);
            _isChecked = false;
            setCallback(_callbackOn);
        }
        
		event->stopPropagation();
        
		return true;
	}

	void CheckBox::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * event)
	{
	}

	void CheckBox::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * event)
	{
        /*
		_normal->setVisible(true);
		_checked->setVisible(false);
        */
        
        if (_callback)
            _callback(this);
    }

    CheckBox::CheckBox()
    {
        
    }
    
	CheckBox::~CheckBox()
	{
	}
	
	void CheckBox::setCallback(const std::function<void(CheckBox*)> callback)
	{
		_callback = callback;
	}
    
    void CheckBox::setCallbackOn(const std::function<void(CheckBox*)> callback)
    {
        _callbackOn = callback;
    }
    
    void CheckBox::setCallbackOff(const std::function<void(CheckBox*)> callback)
    {
        _callbackOff = callback;
    }
}
