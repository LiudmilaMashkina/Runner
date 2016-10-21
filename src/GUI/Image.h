#pragma once

#include "View.h"
#include "2d/CCSprite.h"
#include "gui/ScalePolicy.h"

namespace gui
{
	class Image : public View
	{
	public:
		~Image();
		static std::shared_ptr<Image> create(const std::string &fileName, ScalePolicy policy);
		void setSize(const cocos2d::Vec2 &size) override;
		cocos2d::Vec2 getSize() const override;
		cocos2d::Sprite* getSprite() { return _sprite; };

	private:
		Image(cocos2d::Node* node, const std::string &fileName, ScalePolicy policy);
		cocos2d::Sprite* _sprite = nullptr;

		ScalePolicy _policy;
	};
}
