#pragma once

#include "2d/CCSprite.h"
#include "Utils/MacroCreate.h"

namespace gui2
{
    class Button : public cocos2d::Node
	{
	public:
        CC_CREATE_FUNC_2(Button, initWith,
                         const std::string&, normal,
                         const std::string&, pressed);
        
		void setCallback(const std::function<void(Button*)> callback);
        
        void setEnabled(bool enabled) {_enabled = enabled;}
        
        virtual void setOpacity(GLubyte opacity) override;

	private:
		bool initWith(const std::string &normal, const std::string &pressed);

		bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
		void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
		void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

		cocos2d::Sprite* _normal = nullptr;
		cocos2d::Sprite* _pressed = nullptr;

		std::function<void(Button*)> _callback;
        
        bool _enabled = true;
	};

}

