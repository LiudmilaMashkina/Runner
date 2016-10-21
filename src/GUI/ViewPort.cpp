#include "ViewPort.h"

namespace gui
{
	std::shared_ptr<ViewPort> ViewPort::create(cocos2d::Node * node)
	{
		std::shared_ptr<ViewPort> viewPort(new ViewPort(node));
		return viewPort;
	}

	ViewPort::ViewPort(cocos2d::Node* node)
	{
		setNode(node);
	}


	ViewPort::~ViewPort()
	{
	}
}


