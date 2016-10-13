//
//  Generator.cpp
//  Wanderer
//
//  Created by Luda on 14/05/16.
//
//

#include "FieldMixer.h"
#include "Utils/b2Vec2Operators.h"

FieldMixer::FieldMixer(const std::shared_ptr<IForceField> &field1,
	const std::shared_ptr<IForceField> &field2,
	const std::function<float()> &cft1,
	const std::function<float()> &cft2) :
_field1(field1),
_field2(field2),
_cft1(cft1),
_cft2(cft2)
{}

std::shared_ptr<FieldMixer> FieldMixer::create(
	const std::shared_ptr<IForceField> &field1,
	const std::shared_ptr<IForceField> &field2,
	const std::function<float()> &cft1,
	const std::function<float()> &cft2)
{
	return std::shared_ptr<FieldMixer>(new FieldMixer(field1, field2, cft1, cft2));
}

b2Vec2 FieldMixer::getForce(const b2Vec2 &position)
{
	b2Vec2 force1 = _field1->getForce(position);
	b2Vec2 force2 = _field2->getForce(position);

	return force1 * _cft1() + force2 * _cft2();
}



