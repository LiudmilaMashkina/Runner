#pragma once

#include <memory>
#include "IForceField.h"

class ITimeProvider;

class ForceFieldFactory
{
public:
	static std::shared_ptr<IForceField> createWindField(const std::shared_ptr<ITimeProvider> &timeProvider, 
		const b2Vec2 &fieldSize);
	static std::shared_ptr<IForceField> createWindUpField(const std::shared_ptr<ITimeProvider> &timeProvider,
		const b2Vec2 &fieldSize);
};
