#pragma once

class ITimeProvider
{
public:
	virtual float getTime() = 0;
	virtual ~ITimeProvider() {}
};
