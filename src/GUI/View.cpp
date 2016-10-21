#include "View.h"

USING_NS_CC;

namespace gui
{
	View::View()
	{
	}
    
    std::shared_ptr<View> View::create()
    {
        std::shared_ptr<View> view(new View());
        
        Node* node = Node::create();
        view->setNode(node);
        
        return view;
    }

	View::~View()
	{ 
	}

	void View::setSize(const cocos2d::Vec2 &size)
	{
        cocos2d::Size s;
        s.width = size.x;
        s.height = size.y;
        _node->setContentSize(s);
    }

	void View::setWidth(float width)
	{
        setSize({ width, getSize().y });
	}

	void View::setHeight(float height)
	{
		setSize({ getSize().x, height });
	}
	
	cocos2d::Vec2 View::getSize() const
	{
        cocos2d::Size s = _node->getContentSize();

        return cocos2d::Vec2(s.width, s.height);
	}

	void View::setVisible(bool isVisible)
	{
		_node->setVisible(isVisible);
		
		//if (_views.size() > 0)
		
		for (int i = 0; i < _views.size(); ++i)
		{
			_views[i]->getNode()->setVisible(isVisible);
		}
	}

	void View::setPosition(const Vec2 & pos)
	{
		_node->setPosition(pos);
	}

	void View::setPosX(float posX)
	{
		_node->setPositionX(posX);
	}

	void View::setPosY(float posY)
	{
		_node->setPositionY(posY);
	}

	cocos2d::Vec2 View::getPosition() const
	{
		return getNode()->getPosition();
	}

	void View::addView(const std::shared_ptr<View> &view)
	{
		cocos2d::Node* viewNode = view->getNode();
		_node->addChild(viewNode);
		_views.push_back(view);
	}

	void View::setLayout(const std::shared_ptr<ILayout>& layout)
	{
		_layout = layout;
	}

	void View::setMargin(float left, float right, float top, float bottom)
	{
		_margins.left = left;
		_margins.right = right;
		_margins.top = top;
		_margins.bottom = bottom;
	}

	void View::setMargin(const Margins &margins)
	{
		_margins = margins;
	}

	Margins View::getMargins() const
	{
		return _margins;
	}

	const std::vector<std::shared_ptr<View>> & View::getChildren() const
	{
		return _views;
	}

	void View::setNode(cocos2d::Node* node)
	{
		assert(!_node);
		_node = node;
		_node->setAnchorPoint(Vec2(0, 0));
	}
}
