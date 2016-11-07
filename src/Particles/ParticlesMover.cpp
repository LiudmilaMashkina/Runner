#pragma warning(push, 0)
#pragma warning(pop)

#include "ParticlesMover.h"
#include "ForceField/IForceField.h"
#include "Particle.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/Convert.h"

ParticlesMover::ParticlesMover(const std::shared_ptr<IForceField> &forceField, float airResistance) :
_forceField(forceField),
_airResistance(airResistance)
{}

std::shared_ptr<ParticlesMover> ParticlesMover::create(const std::shared_ptr<IForceField> &forceField, float airResistance)
{
    return std::shared_ptr<ParticlesMover>(new ParticlesMover(forceField, airResistance));
}

IParticlesUpdater::Action ParticlesMover::updateParticle(Particle &particle, float delta)
{
    particle.ttl -= delta;
    float decrOpacity = 255.0f / (particle.constTtl / delta);
    
    if (particle.ttl <= 0.0f)
    {
        return Action::Remove;
    }
    
    b2Vec2 particlePos = Convert::toMeters(particle.sprite->getPosition());
    b2Vec2 particleForce = _forceField->getForce(particlePos);
    b2Vec2 airResistanceForce = getResistanceForce(particle);
    b2Vec2 totalForce = airResistanceForce + particleForce;
    b2Vec2 acceleration = totalForce / particle.mass;
    particle.velocity += acceleration * delta;
    particlePos += particle.velocity * delta;
    
    particle.sprite->setPosition(Convert::toPixels(particlePos));
    particle.sprite->setOpacity(particle.opacity);
    particle.opacity -= decrOpacity;

    return Action::Nothing;
}

b2Vec2 ParticlesMover::getResistanceForce(const Particle &particle)
{
    float resistanceForce = _airResistance * particle.velocity.LengthSquared();
    
    if (particle.velocity.Length() < 0.1)
        return b2Vec2(0, 0);
    
    b2Vec2 unitVelocity;
    unitVelocity.x = particle.velocity.x / particle.velocity.Length();
    unitVelocity.y = particle.velocity.y / particle.velocity.Length();
    
    b2Vec2 res = -unitVelocity * resistanceForce;
    
    return res;
}

