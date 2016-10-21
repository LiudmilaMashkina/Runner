#pragma once
#include <2d/CCDrawNode.h>


class BorderdNode : public cocos2d::DrawNode
{
public:
	CREATE_FUNC(BorderdNode);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
};
