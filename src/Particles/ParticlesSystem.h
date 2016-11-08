#pragma once

#include <list>
#include <vector>
#include <memory>
#include "Particle.h"
#include "IUpdatable.h"
#include "Utils/MacroCreate.h"

class IParticlesUpdater;
class ISystemUpdater;

class ParticlesSystem : public IUpdatable
{
public:
    CREATE_FUNC_0(ParticlesSystem);
    
    virtual void update(float delta) override;
    
    void addParticle(const Particle &particle);
    void addParticlesUpdater(std::shared_ptr<IParticlesUpdater> pUpdater);
    void addSystemUpdater(std::shared_ptr<ISystemUpdater> sUpdater);
    size_t getParticleCount() const;
    
private:
    ParticlesSystem();
    
    std::list<Particle> _particles;
    std::vector<std::shared_ptr<IParticlesUpdater>> _pUpdaters;
    std::vector<std::shared_ptr<ISystemUpdater>> _sUpdaters;
};

