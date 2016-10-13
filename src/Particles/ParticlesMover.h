#pragma once

#include <Box2D/Common/b2Math.h>
#include <memory>
#include "IParticlesUpdater.h"

class IForceField;
struct Particle;

class ParticlesMover : public IParticlesUpdater
{
public:
    virtual IParticlesUpdater::Action updateParticle(Particle &particle, float delta) override;
    
    static std::shared_ptr<ParticlesMover> create(const std::shared_ptr<IForceField> &forceField, float airResistance);
    
    b2Vec2 getResistanceForce(const Particle &particle);
private:
    ParticlesMover(const std::shared_ptr<IForceField> &forceField, float airResistance);
    
    std::shared_ptr<IForceField> _forceField;
    float _airResistance = 0.0f;
};

