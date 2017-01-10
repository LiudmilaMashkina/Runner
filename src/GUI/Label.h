#pragma once

#include "View.h"
#include "2d/CCSprite.h"

namespace gui
{
	class Label : public View
	{
	public:
		~Label();
		static std::shared_ptr<Label> create(const std::string &base, const std::string &text, const std::string &ttfFile, float textSize);
        void setNum(int val);
        
		
	private:
		Label(cocos2d::Node* node, const std::string &base, const std::string &progress, const std::string &ttfFile, float textSize);

		cocos2d::Sprite* _base = nullptr;
        cocos2d::Label* _label = nullptr;
    };

}

