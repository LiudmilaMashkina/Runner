#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "ParticlesObject.h"
#include "Particles/ParticlesGenerator.h"
#include "Particles/ParticlesSystem.h"
#include "Utils/Convert.h"
#include "GameWorld.h"

ParticlesObject::ParticlesObject(const ParticlesFactory::GeneratorInfo& particleSystem, GameWorld* world) :
_particleSystem(particleSystem),
_world(world)
{}

ParticlesObject::~ParticlesObject()
{
    _particleSystem.particlesNode->removeFromParentAndCleanup(true);
}

void ParticlesObject::update(float delta)
{
    if (_particleSystem.particlesGenerator->isPaused())
    {
        int count = _particleSystem.particlesSystem->getParticleCount();
        if (count == 0)
        {
            _world->removeObjectLater(this);
        }
    }
    _particleSystem.particlesSystem->update(delta);
}

b2Vec2 ParticlesObject::getPosition()
{
    return Convert::toMeters(_particleSystem.particlesNode->getPosition());
}

GameObjectType ParticlesObject::getType() const
{
    return GameObjectType::PariclesObject;
}

void ParticlesObject::setPaused(bool paused)
{
    _particleSystem.particlesGenerator->setPaused(paused);
}
