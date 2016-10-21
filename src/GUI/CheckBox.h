#pragma once

#include <2d/CCSprite.h>
#include "View.h"
#include "Utils/MacroCreate.h"

namespace gui
{
	class CheckBox : public View
	{
	public:
		~CheckBox();
		
        static std::shared_ptr<CheckBox> create(const std::string &normal, const std::string &checked);
		void setCallback(const std::function<void(CheckBox*)> callback);
        
	private:
		CheckBox(cocos2d::Node* node, const std::string &normal, const std::string &checked);

		bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
		void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
		void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

		cocos2d::Sprite* _normal = nullptr;
		cocos2d::Sprite* _checked = nullptr;
        bool _isChecked = false;
		std::function<void(CheckBox*)> _callback;
	};

}

