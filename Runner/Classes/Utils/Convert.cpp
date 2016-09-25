#pragma warning(push, 0)

#pragma warning(pop)
#define _USE_MATH_DEFINES
#include <cmath>
#include "Convert.h"
#include "Environment.h"

USING_NS_CC;

b2Vec2 Convert::toMeters(const Vec2 &value)
{
	b2Vec2 result;
	result.x = value.x / Environment::getPTMratio();
	result.y = value.y / Environment::getPTMratio();

	return result;
}

float Convert::toMeters(float value)
{
	float result;
	result = value / Environment::getPTMratio();

	return result;
}

Vec2 Convert::toPixels(const b2Vec2 &value)
{
	Vec2 result;
	result.x = value.x * Environment::getPTMratio();
	result.y = value.y * Environment::getPTMratio();

	return result;
}

float Convert::toPixels(float value)
{
	return value * Environment::getPTMratio();
}

float Convert::toDegrees(float radians)
{
	return 180.0f * radians / float(M_PI);
}



