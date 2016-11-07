#pragma warning(push, 0)
#pragma warning(pop)

#include "ParticlesSystem.h"
#include "IParticlesUpdater.h"
#include "ISystemUpdater.h"
#include "Particle.h"

ParticlesSystem::ParticlesSystem()
{
    
}

std::shared_ptr<ParticlesSystem> ParticlesSystem::create()
{
    return std::shared_ptr<ParticlesSystem>(new ParticlesSystem());
}

void ParticlesSystem::addParticlesUpdater(std::shared_ptr<IParticlesUpdater> pUpdater)
{
    _pUpdaters.push_back(pUpdater);
}

void ParticlesSystem::addSystemUpdater(std::shared_ptr<ISystemUpdater> sUpdater)
{
    _sUpdaters.push_back(sUpdater);
}

int ParticlesSystem::getParticleCount() const
{
    return _particles.size();
}

void ParticlesSystem::addParticle(const Particle &particle)
{
    _particles.push_back(particle);
}

void ParticlesSystem::update(float delta)
{
    for (std::list<Particle>::iterator it = _particles.begin(); it != _particles.end();)
    {
        Particle &p = *it;
        bool removed = false;
        for (int i = 0; i < _pUpdaters.size(); ++i)
        {
            IParticlesUpdater::Action action = _pUpdaters[i]->updateParticle(p, delta);
            if (action == IParticlesUpdater::Action::Remove)
            {
                p.sprite->removeFromParentAndCleanup(true);
                it = _particles.erase(it);
                removed = true;
                break;
            }
        }
        
        if (!removed)
            ++it;
    }
    
    for (int i = 0; i < _sUpdaters.size(); ++i)
        _sUpdaters[i]->update(delta, *this);
}
