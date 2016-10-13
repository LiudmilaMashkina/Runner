#include "ForceFieldFactory.h"
#include "Utils/ITimeProvider.h"
#include "GridForceField.h"
#include "Utils/b2Vec2Operators.h"
#include "StaticForceField.h"
#include "ForceField/Clamper.h"
#include "FieldMixer.h"

std::shared_ptr<IForceField> ForceFieldFactory::createWindField(const std::shared_ptr<ITimeProvider> &timeProvider, 
	const b2Vec2 &fieldSize)
{
	auto calm = GridForceField::create(fieldSize, 0.1);
	calm->setStatic(b2Vec2(-3, 0));

	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x / 2;
		whirl.center.y = fieldSize.y / 3;

		whirl.outer.radius = fieldSize.x / 4;
		whirl.outer.radialForce = 2;
		whirl.outer.tangentialForce = 0.1;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 1;
		whirl.inner.tangentialForce = 7;

		calm->addWhirl(whirl);
	}

	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x / 6.0f;
		whirl.center.y = fieldSize.y * 3.0f / 4.0f;

		whirl.outer.radius = fieldSize.x / 7.0f;
		whirl.outer.radialForce = 4;
		whirl.outer.tangentialForce = -0.3;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 1;
		whirl.inner.tangentialForce = -7;

		calm->addWhirl(whirl);
	}
	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x * 5.0f / 6.0f;
		whirl.center.y = fieldSize.y * 2.0f / 3.0f;

		whirl.outer.radius = fieldSize.y / 3.0f;
		whirl.outer.radialForce = 4;
		whirl.outer.tangentialForce = -0.3;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 1;
		whirl.inner.tangentialForce = -7;

		calm->addWhirl(whirl);
	}

	auto burst = GridForceField::create(fieldSize, 0.1);
	burst->setStatic(b2Vec2(-4, 1));
	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x / 2.0f;
		whirl.center.y = fieldSize.y * 2.0f / 3.0f;

		whirl.outer.radius = fieldSize.x / 4;
		whirl.outer.radialForce = 2;
		whirl.outer.tangentialForce = 0.1;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 1;
		whirl.inner.tangentialForce = 7;

		burst->addWhirl(whirl);
	}
	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x / 6.0f;
		whirl.center.y = fieldSize.y / 4.0f;

		whirl.outer.radius = fieldSize.x / 7.0f;
		whirl.outer.radialForce = 4;
		whirl.outer.tangentialForce = -0.3;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 1;
		whirl.inner.tangentialForce = -7;

		burst->addWhirl(whirl);
	}
	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x * 5.0f / 6.0f;
		whirl.center.y = fieldSize.y / 3.0f;

		whirl.outer.radius = fieldSize.y / 3.0f;
		whirl.outer.radialForce = 4;
		whirl.outer.tangentialForce = -0.3;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 1;
		whirl.inner.tangentialForce = -7;

		burst->addWhirl(whirl);
	}

	auto mixer = FieldMixer::create(calm, burst,
		[=]() {return 1;},
		[=]() {
			float t = timeProvider->getTime();
			return fabs(sinf(t));
		});

	auto clamper = Clamper::create(mixer, fieldSize);

	return clamper;
}


std::shared_ptr<IForceField> ForceFieldFactory::createWindUpField(const std::shared_ptr<ITimeProvider> &timeProvider,
	const b2Vec2 &fieldSize)
{
	auto calm = GridForceField::create(fieldSize, 0.1);
	calm->setStatic(b2Vec2(0, 3));
	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x / 2;
		whirl.center.y = fieldSize.y;

		whirl.outer.radius = fieldSize.x / 2;
		whirl.outer.radialForce = 10;
		whirl.outer.tangentialForce = 0;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 5;
		whirl.inner.tangentialForce = 0;

		calm->addWhirl(whirl);
	}

	auto burst = GridForceField::create(fieldSize, 0.1);
	burst->setStatic(b2Vec2(-4, 1));
	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x / 5.0f;
		whirl.center.y = fieldSize.x / 5.0f;

		whirl.outer.radius = fieldSize.x / 4;
		whirl.outer.radialForce = 2;
		whirl.outer.tangentialForce = 0.1;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 1;
		whirl.inner.tangentialForce = 7;

		burst->addWhirl(whirl);
	}
	{
		GridForceField::WhirlDef whirl;
		whirl.center.x = fieldSize.x / 5.0f * 4.0f;
		whirl.center.y = fieldSize.y / 4.0f * 3.0f;

		whirl.outer.radius = fieldSize.x / 4;
		whirl.outer.radialForce = 2;
		whirl.outer.tangentialForce = -0.1;

		whirl.inner.radius = 0.1;
		whirl.inner.radialForce = 1;
		whirl.inner.tangentialForce = -7;

		burst->addWhirl(whirl);
	}

	auto mixer = FieldMixer::create(calm, burst,
		[=]() {return 1;},
		[=]() {
			float t = timeProvider->getTime();
			return fabs(sinf(t));
		});

	auto clamper = Clamper::create(mixer, fieldSize);

	return clamper;
}
