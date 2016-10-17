#pragma once

#include "ITimeProvider.h"
#include "IUpdatable.h"
#include <memory>

class TimeProvider : public ITimeProvider, public IUpdatable
{
public:
	virtual float getTime() override;
	virtual void update(float delta) override;
	static std::shared_ptr<TimeProvider> create();

private:
	TimeProvider() {}

	float _time = 0.0;
};
