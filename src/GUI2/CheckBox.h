#pragma once

#include <2d/CCSprite.h>
#include "Utils/MacroCreate.h"

namespace gui2
{
    class CheckBox : public cocos2d::Node
	{
	public:
		virtual ~CheckBox();
		
  		void setCallbackOn(const std::function<void(CheckBox*)> callback);
        void setCallbackOff(const std::function<void(CheckBox*)> callback);
        
        CC_CREATE_FUNC_3(CheckBox, initWith,
                         const std::string&, normal,
                         const std::string&, checked,
                         bool, condition);
        
        virtual void setOpacity(GLubyte opacity) override;
        
        void setEnabled(bool enabled) {_enabled = enabled;}
        
        
	private:
        CheckBox();
        
        void setCallback(const std::function<void(CheckBox*)> callback);
        
		bool initWith(const std::string &normal, const std::string &checked, bool condition);

		bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
		void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
		void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

		cocos2d::Sprite* _normal = nullptr;
		cocos2d::Sprite* _checked = nullptr;
        bool _isChecked = false;
        std::function<void(CheckBox*)> _callbackOn;
        std::function<void(CheckBox*)> _callbackOff;
		std::function<void(CheckBox*)> _callback;
        
        
        bool _enabled = true;
	};
}

