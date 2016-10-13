#pragma warning(push, 0)
#pragma warning(pop)

#include "ParticlesReplacer.h"
#include "Utils/Convert.h"
#include "Utils/Environment.h"
#include "Particle.h"

IParticlesUpdater::Action ParticlesReplacer::updateParticle(Particle &particle, float delta)
{
    const float overlap = 1;
    
    b2Vec2 partPos = Convert::toMeters(particle.sprite->getPosition());
    
    if (partPos.x < _bounds.downLeft.x - overlap)
        partPos.x += Environment::getScreenSize().x + 1.5 * overlap;
    else if (partPos.x > _bounds.upperRight.x + overlap)
        partPos.x -= Environment::getScreenSize().x - 1.5 * overlap;
    
    if (partPos.y < _bounds.downLeft.y - overlap)
        partPos.y += Environment::getScreenSize().y + 1.5 * overlap;
    else if (partPos.y > _bounds.downLeft.y + overlap)
        partPos.y -= Environment::getScreenSize().y - 1.5 * overlap;
    
    particle.sprite->setPosition(Convert::toPixels(partPos));
    
    return IParticlesUpdater::Action::Nothing;
}

void ParticlesReplacer::setBounds(const Bounds &bounds)
{
    _bounds = bounds;
}

std::shared_ptr<ParticlesReplacer> ParticlesReplacer::create()
{
    return std::shared_ptr<ParticlesReplacer>(new ParticlesReplacer());
}

