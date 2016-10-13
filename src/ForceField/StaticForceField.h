#pragma once

#include <Box2D/Common/b2Math.h>
#include <2d/CCLayer.h>
#include "IForceField.h"

class StaticForceField : public IForceField
{
public:
	virtual b2Vec2 getForce(const b2Vec2 &position) override;
	static std::shared_ptr<StaticForceField> create(const b2Vec2 &force);

private:
	StaticForceField(const b2Vec2 &force);

	const b2Vec2 _force;
};
