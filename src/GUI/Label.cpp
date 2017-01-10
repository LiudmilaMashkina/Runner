#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <2d/CCProgressTimer.h>
#include <2d/CCScene.h>
#include <2d/CCLabel.h>
#pragma warning(pop)

#include "Label.h"
#include "gui/BorderdNode.h"

USING_NS_CC;

namespace gui
{
    Label::Label(cocos2d::Node* node, const std::string &base, const std::string &text, const std::string &ttfFile, float textSize)
	{
		Sprite* baseSprite = Sprite::create(base);
		baseSprite->setAnchorPoint(Vec2(0, 0));
		_base = baseSprite;
        node->addChild(baseSprite);

        //_label = cocos2d::Label::createWithTTF(text, "resources/Monster_AG.ttf", 20);
        _label = cocos2d::Label::createWithTTF(text, ttfFile, textSize);
        _label->setColor(Color3B::BLACK);
        _label->setAnchorPoint({0, 0});
        
        //Vec2 labelPos;
        //labelPos.x = baseSprite->getContentSize().width / 2;
        //labelPos.y = baseSprite->getContentSize().height / 2;
        //_label->setPosition(labelPos);
        
        node->addChild(_label);
		node->setContentSize(baseSprite->getContentSize());

        setNode(node);
	}

	Label::~Label()
	{
	}

	std::shared_ptr<Label> Label::create(const std::string &base, const std::string &text,const std::string &ttfFile, float textSize)
	{
		auto node = BorderdNode::create();
		return std::shared_ptr<Label>(new Label(node, base, text, ttfFile, textSize));
	}
    
    void Label::setNum(int val)
    {
        assert(_label);
        
        std::string text = std::to_string(val);
        _label->setString(text);
    }
}
