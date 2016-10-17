#pragma warning(push, 0)
#pragma warning(pop)

#include "ParticlesFactory.h"
#include "ParticlesSystem.h"
#include "ParticlesReplacer.h"
#include "ParticlesGenerator.h"
#include "Utils/Environment.h"
#include "ForceField/ForceFieldFactory.h"
#include "Utils/TimeProvider.h"
#include "ParticlesMover.h"

USING_NS_CC;

ParticlesFactory::GeneratorInfo ParticlesFactory::createGameParticlesSystem(std::shared_ptr<TimeProvider> timeProvider)
{
    b2Vec2 fieldSize = Environment::getScreenSize();
    auto forceField = ForceFieldFactory::createWindUpField(timeProvider, fieldSize);
    
    std::shared_ptr<ParticlesSystem> system(new ParticlesSystem());
    
    ParticlesGenerator::Params gParams;
    gParams.fileName = "resources/particle_16x16.png";
    gParams.rate = 5;
    gParams.velocityRange.set(b2Vec2(0, 1), b2Vec2(0, 2));
    gParams.massRange.set(0.5, 1);
    gParams.position = b2Vec2(Environment::getScreenSize().x / 2.0f, -0.5);
    gParams.generationRange.set(b2Vec2(-7.0f , 0.0f), b2Vec2(7.0f, 0.0f));
    gParams.field = forceField;
    
    ParticlesFactory::GeneratorInfo gInfo;
    gInfo.particlesNode = Node::create();
    
    auto pGenerator = ParticlesGenerator::create(gParams, gInfo.particlesNode);
    system->addSystemUpdater(pGenerator);
    
    auto pMover = ParticlesMover::create(forceField, 2);
    system->addParticlesUpdater(pMover);
    
    auto pReplacer = ParticlesReplacer::create();
    
    ParticlesReplacer::Bounds bounds;
    bounds.downLeft = b2Vec2(0, 0);
    bounds.upperRight = Environment::getScreenSize();
    
    pReplacer->setBounds(bounds);
    
    gInfo.particlesSystem = system;
    gInfo.particlesGenerator = pGenerator;
    
    return gInfo;
}
