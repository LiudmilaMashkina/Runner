#pragma once

#include "View.h"
#include "2d/CCSprite.h"

namespace cocos2d
{
    class ProgressTimer;
}

namespace gui
{
	class ProgressBar : public View
	{
	public:
		~ProgressBar();
		static std::shared_ptr<ProgressBar> create(const std::string &base, const std::string &progress);
        
        void setLifes(int lifes);
		
	private:
		ProgressBar(cocos2d::Node* node, const std::string &base, const std::string &progress);

		cocos2d::Sprite* _base = nullptr;
        cocos2d::ProgressTimer* _progress = nullptr;
	};

}

