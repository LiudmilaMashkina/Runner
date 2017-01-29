#pragma once

#include "View.h"
#include "2d/CCSprite.h"

namespace gui
{
	class Button : public View
	{
	public:
		~Button();
		static std::shared_ptr<Button> create(const std::string &normal, const std::string &pressed);
		void setCallback(const std::function<void(Button*)> callback);
        
        void setEnabled(bool enabled);

	private:
		Button(cocos2d::Node* node, const std::string &normal, const std::string &pressed);

		bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
		void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
		void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

		cocos2d::Sprite* _normal = nullptr;
		cocos2d::Sprite* _pressed = nullptr;

		std::function<void(Button*)> _callback;
        bool _enabled = true;
	};

}

