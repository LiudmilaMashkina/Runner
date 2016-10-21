#pragma once

#include "ILayout.h"
#include "Alignment.h"
#include "Orientation.h"
#include "Utils/MacroCreate.h"
    
namespace gui
{
	class BoxLayout : public ILayout
	{
	public:
		~BoxLayout();
		void doLayout(const std::shared_ptr<View> &view, bool isFixedSize) override;

        CREATE_FUNC_2(BoxLayout, Orientation, orientation, Alignment, alignment);
        
	private:
        BoxLayout(Orientation orientation, Alignment alignment);
        
		void align(View * view,
			const std::function<float(View*)>& getSize,
			const std::function<void (View*, float)>& setSize,
			const std::function<void(View*, float)>& setCoordinate,
			const std::function<float(View*)>& getCoordinate,
			const std::function<float(View*)> &getMarginBefore,
			const std::function<float(View*)> &getMarginAfter,
			bool isFixedSize);
		void lineup(View * view,
			const std::function<float(View*)>& getSize,
			const std::function<void(View*, float)>& setSize,
			const std::function<void(View*, float)>& setCoordinate,
			const std::function<float(View*)> &getMarginBefore,
			const std::function<float(View*)> &getMarginAfter,
			bool isFixedSize);

		Orientation _orientation;
		Alignment _alignment;
	};
}
