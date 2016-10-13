#include "TimeProvider.h"

std::shared_ptr<TimeProvider> TimeProvider::create()
{
	return std::shared_ptr<TimeProvider>(new TimeProvider());
}

void TimeProvider::update(float delta)
{
	_time += delta;
}

float TimeProvider::getTime()
{
	return _time;
}
