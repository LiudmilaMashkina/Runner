#pragma once

#include <2d/CCNode.h>
#include "ILayout.h"
#include "Utils/MacroCreate.h"

namespace gui
{
	typedef cocos2d::Vec2 Vec2;

	struct Margins
	{
		float left;
		float right;
		float top;
		float bottom;
	};

	class View
	{
	public:
		virtual ~View();

		virtual void setSize(const Vec2 &size);
		void setWidth(float width);
		void setHeight(float height);
		virtual Vec2 getSize() const;
		virtual void setVisible(bool isVisible);

		void setPosition(const Vec2 &pos);
		void setPosX(float posX);
		void setPosY(float posY);
		cocos2d::Vec2 getPosition() const;
		
        void addView(const std::shared_ptr<View> &view);
		
        void setLayout(const std::shared_ptr<ILayout> &layout);
		void setMargin(float left, float right, float top, float bottom);
		void setMargin(const Margins &margins);
		Margins getMargins() const;
		const std::vector<std::shared_ptr<View>> & getChildren() const ;
		cocos2d::Node* getNode() const { return _node; };
        
        static std::shared_ptr<View> create();
        
	protected:
		View();
		void setNode(cocos2d::Node* node);
	
	private:
		cocos2d::Node* _node = nullptr;
		std::vector<std::shared_ptr<View>> _views;
		std::shared_ptr<ILayout> _layout;
		Margins _margins;
	};
}
