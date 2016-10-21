#include "Image.h"
#include "2d/CCSprite.h"
#include "gui/BorderdNode.h"

namespace gui
{
	Image::Image(cocos2d::Node* node, const std::string &fileName, ScalePolicy policy) :
		_policy(policy)
	{
		cocos2d::Sprite* sprite = cocos2d::Sprite::create(fileName);
		sprite->setAnchorPoint(Vec2(0, 0));
		_sprite = sprite;
		node->setContentSize(sprite->getContentSize());
		node->addChild(sprite);
		sprite->setPosition(node->getContentSize() / 2 - sprite->getContentSize() / 2);
		setNode(node);
	}


	Image::~Image()
	{

	}


	std::shared_ptr<Image> Image::create(const std::string &fileName, ScalePolicy policy)
	{
		auto node = BorderdNode::create();
		return std::shared_ptr<Image>(new Image(node, fileName, policy));
	}

	void Image::setSize(const cocos2d::Vec2 & size)
	{
        cocos2d::Size s;
        s.width = size.x;
        s.height = size.y;
        
		cocos2d::Node* node = getNode();
		node->setContentSize(s);
		cocos2d::Size spriteSize = _sprite->getContentSize();
		Vec2 scale;
		scale.x = s.width / spriteSize.width;
		scale.y = s.height / spriteSize.height;
		
		switch (_policy)
		{
		case ScalePolicy::Fit:
			if (scale.x <= scale.y)
			{
				_sprite->setScale(scale.x);
				scale.y = scale.x;
			}
			else
			{
				_sprite->setScale(scale.y);
				scale.x = scale.y;
			}
			break;
		case ScalePolicy::Stretch:
			_sprite->setScale(scale.x, scale.y);
			break;
		default:
			assert(false);
			break;
		}
		Vec2 spritePos;
		spritePos.x = s.width / 2 - spriteSize.width * scale.x / 2;
		spritePos.y = s.height / 2 - spriteSize.height * scale.y / 2;
		_sprite->setPosition(spritePos);		
	}

	cocos2d::Vec2 Image::getSize() const
	{
        cocos2d::Size s = getNode()->getContentSize();
        cocos2d::Vec2 size;
        size.x = s.width;
        size.y = s.height;
        
        return size;
	}
}
