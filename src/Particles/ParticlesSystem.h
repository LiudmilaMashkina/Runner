#pragma once

#include <list>
#include <vector>
#include <memory>
#include "Particle.h"

class IParticlesUpdater;
class ISystemUpdater;

class ParticlesSystem
{
public:
    void update(float delta);
    void addParticle(const Particle &particle);
    void addParticlesUpdater(std::shared_ptr<IParticlesUpdater> pUpdater);
    void addSystemUpdater(std::shared_ptr<ISystemUpdater> sUpdater);
    
private:
    std::list<Particle> _particles;
    std::vector<std::shared_ptr<IParticlesUpdater>> _pUpdaters;
    std::vector<std::shared_ptr<ISystemUpdater>> _sUpdaters;
};

