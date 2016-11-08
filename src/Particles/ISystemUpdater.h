#pragma once

class ParticlesSystem;

class ISystemUpdater
{
public:
	virtual ~ISystemUpdater() {}
	virtual void update(float delta, ParticlesSystem& system) = 0;
};

