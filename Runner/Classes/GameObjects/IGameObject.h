#pragma once

#pragma warning(push, 0)

#pragma warning(pop)

class IGameObject 
{
public:
	virtual ~IGameObject() {};

	virtual void update(float delta) = 0;
};