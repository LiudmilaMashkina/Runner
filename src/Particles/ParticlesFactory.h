#pragma once

#include <memory>
#include <2d/CCNode.h>
#include <Box2D/Common/b2Math.h>

class ParticlesSystem;
class TimeProvider;
class ParticlesGenerator;
class ParticleGeneratorGroup;

class ParticlesFactory
{
public:
    struct ParticleSystemControls
    {
        cocos2d::Node* particlesNode = nullptr;
        std::shared_ptr<ParticlesSystem> particlesSystem;
        std::shared_ptr<ParticleGeneratorGroup> generatorGroup;
    };
    
    static ParticleSystemControls createGameParticlesSystem(const std::shared_ptr<TimeProvider>& timeProvider);
    static ParticleSystemControls createMainMenuParticlesSystem(const std::shared_ptr<TimeProvider>& timeProvider);
    static ParticleSystemControls createBombParticles(const std::shared_ptr<TimeProvider>& timeProvider, cocos2d::Node* partNode);
    static ParticleSystemControls createGrassParticles(const std::shared_ptr<TimeProvider>& timeProvider, cocos2d::Node* partNode, const b2Vec2& diapason);
    static ParticleSystemControls createChippingParticles(const std::shared_ptr<TimeProvider>& timeProvider, cocos2d::Node* partNode, const std::vector<std::string>& fileNames);
    
    static ParticleSystemControls createMainMenuFireParticleSystem(const std::shared_ptr<TimeProvider>& timeProvider, cocos2d::Node* parentNode);

};
