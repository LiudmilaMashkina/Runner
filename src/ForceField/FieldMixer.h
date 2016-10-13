#pragma once

#include "IForceField.h"
#include <functional>

class FieldMixer : public IForceField
{
public:
	static std::shared_ptr<FieldMixer> create(
		const std::shared_ptr<IForceField> &field1, 
		const std::shared_ptr<IForceField> &field2,
		const std::function<float()> &cft1,
		const std::function<float()> &cft2);
	virtual b2Vec2 getForce(const b2Vec2 &position) override;

private:
	FieldMixer(const std::shared_ptr<IForceField> &field1, 
		const std::shared_ptr<IForceField> &field2, 
		const std::function<float()> &cft1,
		const std::function<float()> &cft2);

	std::shared_ptr<IForceField> _field1;
	std::shared_ptr<IForceField> _field2;
	std::function<float()> _cft1;
	std::function<float()> _cft2;
};
