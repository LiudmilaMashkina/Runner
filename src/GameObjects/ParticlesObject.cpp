#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "ParticlesObject.h"
#include "Particles/ParticlesSystem.h"
#include "Particles/ParticleGeneratorGroup.h"
#include "Utils/Convert.h"
#include "GameWorld.h"

ParticlesObject::ParticlesObject(const ParticlesFactory::ParticleSystemControls& particleSystem, GameWorld* world) :
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
    _particleSystem.particlesSystem->update(delta);
    
    if (_removeOnZeroParticles)
    {
        size_t count = _particleSystem.particlesSystem->getParticleCount();
        if (count == 0)
        {
            _world->removeObjectLater(this);
            return;
        }
    }
}

b2Vec2 ParticlesObject::getPosition()
{
    return _particleSystem.generatorGroup->getPosition();
}

GameObjectType ParticlesObject::getType() const
{
    return GameObjectType::PariclesObject;
}

void ParticlesObject::setPaused(bool paused)
{
    _particleSystem.generatorGroup->setPaused(paused);
}

void ParticlesObject::setPosition(const b2Vec2 &pos)
{
    _particleSystem.generatorGroup->setPosition(pos);
}
