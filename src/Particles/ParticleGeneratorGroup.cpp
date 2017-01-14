#pragma warning(push, 0)

#pragma warning(pop)

#include "ParticlesGenerator.h"
#include "ParticleGeneratorGroup.h"

ParticleGeneratorGroup::ParticleGeneratorGroup(const std::vector<std::shared_ptr<ParticlesGenerator>>& generators) :
_generators(generators)
{
    assert(!generators.empty());
}

ParticleGeneratorGroup::ParticleGeneratorGroup(const std::shared_ptr<ParticlesGenerator>& generator) :
_generators({generator})
{}

void ParticleGeneratorGroup::setPosition(const b2Vec2& pos)
{
    for (auto& g : _generators)
        g->setPosition(pos);
}

b2Vec2 ParticleGeneratorGroup::getPosition() const
{
    return _generators[0]->getPosition();
}

void ParticleGeneratorGroup::setPaused(bool isPaused)
{
    for (auto& g : _generators)
        g->setPaused(isPaused);
}

bool ParticleGeneratorGroup::isPaused() const
{
    return _generators[0]->isPaused();
}
