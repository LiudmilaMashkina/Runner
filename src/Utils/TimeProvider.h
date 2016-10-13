#pragma once

#include "ITimeProvider.h"
#include <memory>

class TimeProvider : public ITimeProvider
{
public:
	virtual float getTime() override;
	void update(float delta);
	static std::shared_ptr<TimeProvider> create();

private:
	TimeProvider() {}

	float _time = 0.0;
};
