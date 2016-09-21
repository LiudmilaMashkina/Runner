#pragma once

#pragma warning(push, 0)

#pragma warning(pop)

//USING_NS_CC;

class IGameObject 
{
public:
	virtual ~IGameObject() {};

	virtual void update(float delta) = 0;
};