#pragma once

#include <2d/CCSprite.h>
#include "Utils/MacroCreate.h"

namespace cocos2d
{
    class ProgressTimer;
}

namespace gui2
{
	class ProgressBar : public cocos2d::Node
	{
	public:
		~ProgressBar();
		
        CC_CREATE_FUNC_2(ProgressBar, initWith, const std::string&, base, const std::string&, progress);
        
        void setProgress(int percents);
        void setProgressColor(const cocos2d::Color3B& color);
		
	private:
		bool initWith(const std::string &base, const std::string &progress);

		cocos2d::Sprite* _base = nullptr;
        cocos2d::ProgressTimer* _progress = nullptr;
	};
}

