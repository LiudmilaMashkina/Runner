#pragma once

#include <Box2D/Common/b2Math.h>

class IForceField
{
public:
	virtual b2Vec2 getForce(const b2Vec2 &pos) = 0;
	virtual ~IForceField() {}
};
