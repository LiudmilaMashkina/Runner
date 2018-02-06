#include "CheckBox.h"
#include "GUI/BorderdNode.h"
#include "base/CCEventListenerTouch.h"
#include "base/CCEventDispatcher.h"

namespace gui
{
	CheckBox::CheckBox(cocos2d::Node* node, const std::string &normal, const std::string &checked)
	{
		cocos2d::Sprite* normalSprite = cocos2d::Sprite::create(normal);
		normalSprite->setAnchorPoint(Vec2(0, 0));
		normalSprite->setVisible(true);
		_normal = normalSprite;

		cocos2d::Sprite* checkedSprite = cocos2d::Sprite::create(checked);
		checkedSprite->setAnchorPoint(Vec2(0, 0));
		checkedSprite->setVisible(false);
		_checked = checkedSprite;

		node->setContentSize(normalSprite->getContentSize());
		node->addChild(normalSprite);
		node->addChild(checkedSprite);

		auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
		touchListener->onTouchBegan = CC_CALLBACK_2(CheckBox::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(CheckBox::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(CheckBox::onTouchEnded, this);
		node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, node);

		setNode(node);
	}

	bool CheckBox::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * event)
	{
        if (!_enabled)
            return false;
        
		Vec2 touchPos =	getNode()->convertTouchToNodeSpace(touch);

		cocos2d::Vec2 size = getSize();
		if (touchPos.x < 0 || touchPos.x > size.x || touchPos.y < 0 || touchPos.y > size.y)
			return false;

		if (getNode()->isVisible() == false)
			return false;
        
        if (_isChecked == false)
        {
            _normal->setVisible(false);
            _checked->setVisible(true);
            _isChecked = true;
        }
        else
        {
            _normal->setVisible(true);
            _checked->setVisible(false);
            _isChecked = false;
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


	CheckBox::~CheckBox()
	{
	}

	std::shared_ptr<CheckBox> CheckBox::create(const std::string &normal, const std::string &pressed)
	{
		auto node = BorderdNode::create();
		return std::shared_ptr<CheckBox>(new CheckBox(node, normal, pressed));
	}
	
	void CheckBox::setCallback(const std::function<void(CheckBox*)> callback)
	{
		_callback = callback;
	}

}
