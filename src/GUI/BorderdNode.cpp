#include "BorderdNode.h"

using namespace cocos2d;

void BorderdNode::draw(cocos2d::Renderer * renderer, const cocos2d::Mat4 & transform, uint32_t flags)
{
	Size size = getContentSize();
	clear();
	drawRect({ 0, 0 }, { size.width, size.height }, Color4F::RED);
	DrawNode::draw(renderer, transform, flags);
}
