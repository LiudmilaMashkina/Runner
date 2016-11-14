#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "ParticlesObject.h"
#include "Particles/ParticlesSystem.h"
#include "Utils/Convert.h"
#include "GameWorld.h"

ParticlesObject::ParticlesObject(const ParticlesFactory::GeneratorInfo& particleSystem, GameWorld* world) :
_particleSystem(particleSystem),
_world(world)
{
    assert(_particleSystem.particlesNode == _world->getGraphics());
}

ParticlesObject::~ParticlesObject()
{
}

void ParticlesObject::update(float delta)
{
    if (_particleSystem.particlesGenerator->isPaused())
    {
        size_t count = _particleSystem.particlesSystem->getParticleCount();
        if (count == 0)
        {
            _world->removeObjectLater(this);
            return;
        }
    }
    _particleSystem.particlesSystem->update(delta);
}

b2Vec2 ParticlesObject::getPosition()
{
    return _particleSystem.particlesGenerator->getPosition();
}

GameObjectType ParticlesObject::getType() const
{
    return GameObjectType::PariclesObject;
}

void ParticlesObject::setPaused(bool paused)
{
    _particleSystem.particlesGenerator->setPaused(paused);
}

void ParticlesObject::setPosition(const b2Vec2 &pos)
{
    _particleSystem.particlesGenerator->setPosition(pos);
}
