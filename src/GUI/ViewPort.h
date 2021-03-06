#pragma once

#include "View.h"

namespace gui
{
	class ViewPort : public View
	{
	public:
		~ViewPort();
		static std::shared_ptr<ViewPort> create(cocos2d::Node* node);
        
	protected:
		ViewPort(cocos2d::Node* node);
	};
}

