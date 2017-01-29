#pragma warning(push, 0)
#pragma warning(pop)

#include "ParticlesFactory.h"
#include "ParticlesSystem.h"
#include "ParticlesReplacer.h"
#include "ParticlesGenerator.h"
#include "ParticleGeneratorGroup.h"
#include "Utils/Environment.h"
#include "ForceField/ForceFieldFactory.h"
#include "ForceField/StaticForceField.h"
#include "Utils/TimeProvider.h"
#include "ParticlesMover.h"

USING_NS_CC;

ParticlesFactory::ParticleSystemControls ParticlesFactory::createGameParticlesSystem(const std::shared_ptr<TimeProvider>& timeProvider)
{
    b2Vec2 fieldSize = Environment::getScreenSize();
    auto forceField = ForceFieldFactory::createWindUpField(timeProvider, fieldSize);
    
    std::shared_ptr<ParticlesSystem> system = ParticlesSystem::create();
    
    ParticlesGenerator::Params gParams1;
    gParams1.fileName = "resources/dust_16x16.png";
    gParams1.rate = 5;
    gParams1.velocityRange.set(b2Vec2(0, 1), b2Vec2(0, 2));
    gParams1.massRange.set(0.5, 1);
    gParams1.position = b2Vec2(Environment::getScreenSize().x / 2.0f, -0.5);
    gParams1.generationRange.set(b2Vec2(-7.0f , 0.0f), b2Vec2(7.0f, 0.0f));
    gParams1.field = forceField;
    gParams1.ttlRange.set(7, 15);
    gParams1.widthRange.set(0.1, 0.5);
    
    ParticlesGenerator::Params gParams2;
    gParams2.fileName = "resources/dust_32x32.png";
    gParams2.rate = 3  ;
    gParams2.velocityRange.set(b2Vec2(0, 1), b2Vec2(0, 2));
    gParams2.massRange.set(0.5, 1);
    gParams2.position = b2Vec2(Environment::getScreenSize().x / 2.0f, -0.5);
    gParams2.generationRange.set(b2Vec2(-7.0f , 0.0f), b2Vec2(7.0f, 0.0f));
    gParams2.field = forceField;
    gParams2.ttlRange.set(7, 15);
    gParams2.widthRange.set(0.2, 0.6);
    
    ParticlesGenerator::Params gParams3;
    gParams3.fileName = "resources/dust_64x64.png";
    gParams3.rate = 1  ;
    gParams3.velocityRange.set(b2Vec2(0, 1), b2Vec2(0, 2));
    gParams3.massRange.set(0.5, 1);
    gParams3.position = b2Vec2(Environment::getScreenSize().x / 2.0f, -0.5);
    gParams3.generationRange.set(b2Vec2(-7.0f , 0.0f), b2Vec2(7.0f, 0.0f));
    gParams3.field = forceField;
    gParams3.ttlRange.set(7, 15);
    gParams3.widthRange.set(0.5, 0.8);
    
    
    ParticlesFactory::ParticleSystemControls gInfo;
    gInfo.particlesNode = Node::create();
    
    auto pGenerator1 = ParticlesGenerator::create(gParams1, gInfo.particlesNode);
    system->addSystemUpdater(pGenerator1);
    
    auto pGenerator2 = ParticlesGenerator::create(gParams2, gInfo.particlesNode);
    system->addSystemUpdater(pGenerator2);
    
    auto pGenerator3 = ParticlesGenerator::create(gParams3, gInfo.particlesNode);
    system->addSystemUpdater(pGenerator3);
    
    auto pMover = ParticlesMover::create(forceField, 2);
    system->addParticlesUpdater(pMover);
    
    auto pReplacer = ParticlesReplacer::create();
    
    ParticlesReplacer::Bounds bounds;
    bounds.downLeft = b2Vec2(0, 0);
    bounds.upperRight = Environment::getScreenSize();
    
    pReplacer->setBounds(bounds);
    
    gInfo.particlesSystem = system;
    gInfo.generatorGroup = ParticleGeneratorGroup::create({pGenerator1, pGenerator2, pGenerator3});
    
    return gInfo;
}

ParticlesFactory::ParticleSystemControls ParticlesFactory::createMainMenuParticlesSystem(const std::shared_ptr<TimeProvider>& timeProvider)
{
    b2Vec2 fieldSize = Environment::getScreenSize();
    auto forceField = ForceFieldFactory::createWindUpField(timeProvider, fieldSize);
    
    std::shared_ptr<ParticlesSystem> system = ParticlesSystem::create();
    
    ParticlesGenerator::Params gParams;
    gParams.fileName = "resources/dust_32x32.png";
    gParams.rate = 5;
    gParams.velocityRange.set(b2Vec2(0, 1), b2Vec2(0, 2));
    gParams.massRange.set(0.5, 1);
    gParams.position = b2Vec2(Environment::getScreenSize().x / 2.0f, -0.5);
    gParams.generationRange.set(b2Vec2(-7.0f , 0.0f), b2Vec2(7.0f, 0.0f));
    gParams.field = forceField;
    gParams.ttlRange.set(7, 15);
    gParams.widthRange.set(0.1, 0.5);
    
    ParticlesFactory::ParticleSystemControls gInfo;
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
    gInfo.generatorGroup = ParticleGeneratorGroup::create(pGenerator);
    
    return gInfo;
}

ParticlesFactory::ParticleSystemControls ParticlesFactory::createBombParticles(const std::shared_ptr<TimeProvider>& timeProvider, Node* partNode)
{
    auto forceField = StaticForceField::create(b2Vec2(0, 7));
    std::shared_ptr<ParticlesSystem> system = ParticlesSystem::create();
    
    ParticlesGenerator::Params params;
    params.fileName = "resources/fire_particle_16x16.png";
    params.rate = 14;
    params.velocityRange.set(b2Vec2(0, 0), b2Vec2(0, 0));
    params.massRange.set(0.5, 1);
    params.generationRange.set(b2Vec2(-0.25f, 0.2f), b2Vec2(0.25f, 0.3f));
    params.field = forceField;
    params.ttlRange.set(0.5, 1.0);
    params.widthRange.set(0.1, 0.4);
    
    ParticlesFactory::ParticleSystemControls info;
    info.particlesNode = partNode;
    
    auto generator = ParticlesGenerator::create(params, info.particlesNode);
    system->addSystemUpdater(generator);
    
    auto partMover = ParticlesMover::create(forceField, 0);
    system->addParticlesUpdater(partMover);
    
    info.particlesSystem = system;
    info.generatorGroup = ParticleGeneratorGroup::create(generator);
    
    return info;
}

ParticlesFactory::ParticleSystemControls ParticlesFactory::createGrassParticles(const std::shared_ptr<TimeProvider> &timeProvider, cocos2d::Node *partNode, const b2Vec2& diapason)
{
    auto forceField = StaticForceField::create(b2Vec2(0, 3));
    std::shared_ptr<ParticlesSystem> system = ParticlesSystem::create();
    
    ParticlesGenerator::Params params;
    params.fileName = "resources/black_grass_particle.png";
    params.rate = 20;
    params.velocityRange.set(b2Vec2(0, 0), b2Vec2(0, 0));
    params.massRange.set(0.5, 1);
    params.generationRange.set(b2Vec2(-diapason.x / 2, 0.0f), b2Vec2(diapason.x / 2, 0.0f));
    params.field = forceField;
    params.ttlRange.set(0.3, 0.6);
    params.widthRange.set(0.02, 0.08);
    
    ParticlesFactory::ParticleSystemControls info;
    info.particlesNode = partNode;
    
    auto generator = ParticlesGenerator::create(params, info.particlesNode);
    system->addSystemUpdater(generator);
    
    auto partMover = ParticlesMover::create(forceField, 0);
    system->addParticlesUpdater(partMover);
    
    info.particlesSystem = system;
    info.generatorGroup = ParticleGeneratorGroup::create(generator);
    
    return info;
}

ParticlesFactory::ParticleSystemControls ParticlesFactory::createChippingParticles(const std::shared_ptr<TimeProvider>& timeProvider, cocos2d::Node* partNode, const std::vector<std::string>& fileNames)
{
    auto forceField = StaticForceField::create(b2Vec2(0, -2));
    std::shared_ptr<ParticlesSystem> system = ParticlesSystem::create();
    
    std::vector<std::shared_ptr<ParticlesGenerator>> generators;
    ParticlesFactory::ParticleSystemControls info;
    info.particlesNode = partNode;
    
    
    for (int i = 0; i < fileNames.size(); ++i)
    {
        ParticlesGenerator::Params params;
        params.fileName = fileNames[i];
        params.rate = 0.8;
        params.velocityRange.set(b2Vec2(0, -1), b2Vec2(0, -2));
        params.massRange.set(0.5, 1);
        params.generationRange.set(b2Vec2(-0.05, 0.0f), b2Vec2(0.05, 0.0f));
        params.field = forceField;
        params.ttlRange.set(2.0, 5.0);
        params.widthRange.set(0.1, 0.3);
        
        auto generator = ParticlesGenerator::create(params, info.particlesNode);
        system->addSystemUpdater(generator);
        generators.push_back(generator);
    }
    
    auto partMover = ParticlesMover::create(forceField, 0);
    system->addParticlesUpdater(partMover);
    
    info.particlesSystem = system;
    info.generatorGroup = ParticleGeneratorGroup::create(generators);

    return info;
}

