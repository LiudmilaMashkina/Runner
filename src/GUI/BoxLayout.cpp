#include <algorithm>
#include "BoxLayout.h"
#include "View.h"
#include "GUI/Alignment.h"

namespace gui
{
	BoxLayout::BoxLayout(Orientation orientation, Alignment alignment)
	{
		_orientation = orientation;
		_alignment = alignment;
	}

	BoxLayout::~BoxLayout()
	{
	}
    
	void BoxLayout::doLayout(const std::shared_ptr<View> &view, bool isFixedSize)
	{
		//getSize
		std::function<float(View *)> getSizeX = [](View* view) {return view->getSize().x;};
		std::function<float(View *)> getSizeY = [](View* view) {return view->getSize().y;};

		//setSize
		std::function<void(View*, float)> setSizeX = [](View* view, float size) {view->setWidth(size);};
		std::function<void(View*, float)> setSizeY = [](View* view, float size) {view->setHeight(size);};

		//setCoordinate
		std::function<void(View*, float)> setCoordinateX = [](View* view, float coordinate) {view->setPosX(coordinate);};
		std::function<void(View*, float)> setCoordinateY = [](View* view, float coordinate) {view->setPosY(coordinate);};

		//getCoordinate
		std::function<float(View*)> getCoordinateX = [](View* view) {return view->getPosition().x;};
		std::function<float(View*)> getCoordinateY = [](View* view) {return view->getPosition().y;};

		//getMargin
		std::function<float(View*)> getMarginLeft = [](View* view) {return view->getMargins().left;};
		std::function<float(View*)> getMarginRight = [](View* view) {return view->getMargins().right;};
		std::function<float(View*)> getMarginTop = [](View* view) {return view->getMargins().top;};
		std::function<float(View*)> getMarginBottom = [](View* view) {return view->getMargins().bottom;};
		
		if (_orientation == Orientation::Vertical)
		{	
			align(view.get(), getSizeX, setSizeX, setCoordinateX, getCoordinateX, getMarginLeft, getMarginRight, isFixedSize);
			lineup(view.get(), getSizeY, setSizeY, setCoordinateY, getMarginTop, getMarginBottom, isFixedSize);
		}
		if (_orientation == Orientation::Horizontal)
		{
			align(view.get(), getSizeY, setSizeY, setCoordinateY, getCoordinateY, getMarginTop, getMarginBottom, isFixedSize);
			lineup(view.get(), getSizeX, setSizeX, setCoordinateX , getMarginLeft, getMarginRight, isFixedSize);
		}
	}

	void BoxLayout::align(View * view, 
		const std::function<float(View*)>& getSize, 
		const std::function<void(View*, float)>& setSize,
		const std::function<void(View*, float)>& setCoordinate, 
		const std::function<float(View*)>& getCoordinate,
		const std::function<float(View*)> &getMarginBefore,
		const std::function<float(View*)> &getMarginAfter,
		bool isFixedSize)
	{
		const std::vector<std::shared_ptr<View>> &children = view->getChildren();
        
        if (children.empty())
            return;
        
 		float maxSize = getSize(children[0].get()) + getMarginBefore(children[0].get()) + getMarginAfter(children[0].get());
		float maxChild = getSize(children[0].get());
		float maxMarginBefore = getMarginBefore(children[0].get());
		float maxMarginAfter = getMarginAfter(children[0].get());
		int iterMaxChild = 0;
		for (int i = 1; i < children.size(); ++i)
		{
			float childSize = getSize(children[i].get()) + getMarginBefore(children[i].get()) + getMarginAfter(children[i].get());
			if (childSize > maxSize)
				maxSize = childSize;
			
			float child = getSize(children[i].get());
			if (child > maxChild)
			{
				maxChild = child;
				iterMaxChild = i;
			}
				
			float marginBefore = getMarginBefore(children[i].get());
			if (marginBefore > maxMarginBefore)
				maxMarginBefore = marginBefore;

			float marginAfter = getMarginAfter(children[i].get());
			if (marginAfter > maxMarginAfter)
				maxMarginAfter = marginAfter;
		}

		if (_alignment == Alignment::Left)
		{
			if (isFixedSize == false)
				setSize(view, maxMarginBefore + maxChild + getMarginAfter(children[iterMaxChild].get()));
			
			for (int i = 0; i < children.size(); ++i)
				setCoordinate(children[i].get(), maxMarginBefore);
		}
		else if (_alignment == Alignment::Center)
		{
			if (isFixedSize == false)
				setSize(view, maxSize);

			for (int i = 0; i < children.size(); ++i)
			{
				float coordinate = getSize(view) / 2 - getSize(children[i].get()) / 2;
				setCoordinate(children[i].get(), coordinate);
			}
		}
		else if (_alignment == Alignment::Right)
		{
			if (isFixedSize == false)
   				setSize(view, getMarginBefore(children[iterMaxChild].get()) + maxChild + maxMarginAfter);

			for (int i = 0; i < children.size(); ++i)
			{
				float coordinate = getSize(view) - maxMarginAfter - getSize(children[i].get());
				setCoordinate(children[i].get(), coordinate);
			}
		}
	}

	void BoxLayout::lineup(View * view, 
		const std::function<float(View*)>& getSize, 
		const std::function<void(View*, float)>& setSize,
		const std::function<void(View*, float)>& setCoordinate,
		const std::function<float(View*)> &getMarginBefore,
		const std::function<float(View*)> &getMarginAfter,
		bool isFixedSize)
	{
		const std::vector<std::shared_ptr<View>> &children = view->getChildren();
		float desiredSize = getMarginBefore(children[0].get());
		std::vector<float> centerCoordinates;
		float frontier = getMarginBefore(children[0].get());
		
		for (int i = 0; i < children.size() - 1; ++i)
		{
			float maxMargin = std::max(getMarginAfter(children[i].get()), getMarginBefore(children[i + 1].get()));
			desiredSize += getSize(children[i].get()) + maxMargin;

			float coordinate = frontier + getSize(children[i].get()) / 2; 
			frontier = coordinate + getSize(children[i].get()) / 2 + maxMargin;
			centerCoordinates.push_back(coordinate);
		}
		float lastCoordinate = frontier + getSize(children[children.size() - 1].get()) / 2;
		centerCoordinates.push_back(lastCoordinate);

		desiredSize += getSize(children[children.size() - 1].get()) + getMarginAfter(children[children.size() - 1].get());
		
		float mult = 0;
		if (isFixedSize == false)
		{
			setSize(view, desiredSize);
			mult = 1;
		}
		else
		{
			float parentSize = getSize(view);
			mult = parentSize / desiredSize;
		}
		
		for (int i = 0; i < centerCoordinates.size(); ++i)
		{
			float position = centerCoordinates[i] * mult - getSize(children[i].get()) / 2;
			setCoordinate(children[i].get(), position);
		}
	}
}
