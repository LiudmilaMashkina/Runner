#pragma once

#include<memory>
#include<vector>
#include "ForceField/IForceField.h"

class Clamper : public IForceField
{
public:
	~Clamper() {};
	static std::shared_ptr<Clamper> create(std::shared_ptr<IForceField> forceField, const b2Vec2 &fieldSize);
	b2Vec2 getForce(const b2Vec2 &coordinates) override;

private:
	Clamper(std::shared_ptr<IForceField> forceField, const b2Vec2 &fieldSize);

	std::shared_ptr<IForceField> _forceField;
	const b2Vec2 _fieldSize;
};
