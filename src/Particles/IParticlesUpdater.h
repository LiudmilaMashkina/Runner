#pragma once

struct Particle;

class IParticlesUpdater
{
public:
	enum class Action
	{
		Nothing,
		Remove
	};

	virtual ~IParticlesUpdater() {} 
	virtual Action updateParticle(Particle &particle, float delta) = 0;
};

