#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "ParticlesObject.h"
#include "Particles/ParticlesGenerator.h"
#include "Particles/ParticlesSystem.h"
#include "Utils/Convert.h"
#include "GameWorld.h"

ParticlesObject::ParticlesObject(const ParticlesFactory::GeneratorInfo& particleSystem) :
_particleSystem(particleSystem)
{}

ParticlesObject::~ParticlesObject()
{
    _particleSystem.particlesNode->removeFromParentAndCleanup(true);
}

void ParticlesObject::update(float delta)
{
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
