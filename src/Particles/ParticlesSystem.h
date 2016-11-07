#pragma once

#include <list>
#include <vector>
#include <memory>
#include "Particle.h"
#include "IUpdatable.h"

class IParticlesUpdater;
class ISystemUpdater;

class ParticlesSystem : public IUpdatable
{
public:
    virtual void update(float delta) override;
    
    void addParticle(const Particle &particle);
    void addParticlesUpdater(std::shared_ptr<IParticlesUpdater> pUpdater);
    void addSystemUpdater(std::shared_ptr<ISystemUpdater> sUpdater);
    int getParticleCount() const;
    
    static std::shared_ptr<ParticlesSystem> create();
    
private:
    ParticlesSystem();
    
    std::list<Particle> _particles;
    std::vector<std::shared_ptr<IParticlesUpdater>> _pUpdaters;
    std::vector<std::shared_ptr<ISystemUpdater>> _sUpdaters;
};

