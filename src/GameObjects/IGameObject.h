#pragma once

#pragma warning(push, 0)

#pragma warning(pop)

#include <Box2D/Common/b2Math.h>

class IGameObject 
{
public:
	virtual ~IGameObject() {};

	virtual void update(float delta) = 0;
    virtual b2Vec2 getPosition() = 0;
};
