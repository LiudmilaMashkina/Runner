
#include "Clamper.h"

Clamper::Clamper(std::shared_ptr<IForceField> forceField, const b2Vec2 &fieldSize) :
_forceField(forceField),
_fieldSize(fieldSize)
{}

std::shared_ptr<Clamper> Clamper::create(std::shared_ptr<IForceField> forceField, const b2Vec2 &fieldSize)
{
	return std::shared_ptr<Clamper>(new Clamper(forceField, fieldSize));
}

b2Vec2 Clamper::getForce(const b2Vec2 &coordinates)
{
	b2Vec2 c;
	c.x = fmodf(coordinates.x, _fieldSize.x);
	c.y = fmodf(coordinates.y, _fieldSize.y);

	if (c.x < 0)
		c.x += _fieldSize.x;
	if (c.y < 0)
		c.y += _fieldSize.y;

	return _forceField->getForce(c);
}