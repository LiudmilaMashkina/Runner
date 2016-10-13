
#include "StaticForceField.h"
#include <memory>


std::shared_ptr<StaticForceField> StaticForceField::create(const b2Vec2 &force)
{
	std::shared_ptr<StaticForceField> forceField(new StaticForceField(force));
	return forceField;
}

StaticForceField::StaticForceField(const b2Vec2 &force) :
_force(force)
{}

b2Vec2 StaticForceField::getForce(const b2Vec2 &position)
{
	return _force;
}









