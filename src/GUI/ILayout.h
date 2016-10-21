#pragma once

#include <2d/CCNode.h>

namespace gui
{
	class View;
	
	class ILayout
	{
	public:
		virtual ~ILayout() {}

		// void doLayout(const View &view) = 0;
		virtual void doLayout(const std::shared_ptr<View> &view, bool isFixedSize) = 0;

	};

}
