#pragma once

#include <Box2D/Common/b2Math.h>
#include <memory>
#include "IParticlesUpdater.h"


class ParticlesReplacer : public IParticlesUpdater
{
public:
    struct Bounds
    {
        b2Vec2 downLeft;
        b2Vec2 upperRight;
    };
    
    virtual IParticlesUpdater::Action updateParticle(Particle &particle, float delta) override;
    
    void setBounds(const Bounds &bounds);
    
    static std::shared_ptr<ParticlesReplacer> create();
    
private:
    ParticlesReplacer() {}
    
    Bounds _bounds;
};
