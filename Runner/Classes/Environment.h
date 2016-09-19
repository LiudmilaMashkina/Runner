#pragma once

#pragma warning(push, 0)
#include <Box2D/Common/b2Math.h>
#include <math/Vec2.h>
#pragma warning(pop)

class Environment 
{
public:
	static b2Vec2 getScreenSize();
	static float32 getPTMratio();
};

