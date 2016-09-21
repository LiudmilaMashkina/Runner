#pragma once

#pragma warning(push, 0)
#include <Box2D/Common/b2Math.h>
#include <math/Vec2.h>
#pragma warning(pop)


class Convert 
{
public:
	static b2Vec2 toMeters(const cocos2d::Vec2 &value);
	static float toMeters(float value);
	static cocos2d::Vec2 toPixels(const b2Vec2 &value);
	static float toPixels(float value);
	static float toDegrees(float radians);
};