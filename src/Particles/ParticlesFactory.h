#pragma once

#include <memory>
#include <2d/CCNode.h>
#include <Box2D/Common/b2Math.h>

class ParticlesSystem;
class TimeProvider;
class ParticlesGenerator;

class ParticlesFactory
{
public:
    struct GeneratorInfo
    {
        cocos2d::Node* particlesNode = nullptr;
        std::shared_ptr<ParticlesSystem> particlesSystem;
        std::shared_ptr<ParticlesGenerator> particlesGenerator;
    };
    
    static GeneratorInfo createGameParticlesSystem(std::shared_ptr<TimeProvider> timeProvider);
    static GeneratorInfo createMainMenuParticlesSystem(std::shared_ptr<TimeProvider> timeProvider);
    static GeneratorInfo createBombParticles(std::shared_ptr<TimeProvider> timeProvider);
};
