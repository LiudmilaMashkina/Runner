#pragma once

#include "Utils/MacroCreate.h"

class ParticlesGenerator;

class ParticleGeneratorGroup
{
public:
    CREATE_FUNC_1(ParticleGeneratorGroup, const std::vector<std::shared_ptr<ParticlesGenerator>>&, generators);
    CREATE_FUNC_1(ParticleGeneratorGroup, const std::shared_ptr<ParticlesGenerator>&, generator);
    
    void setPosition(const b2Vec2& pos);
    b2Vec2 getPosition() const;
    
    void setPaused(bool isPaused);
    bool isPaused() const;
    
private:
    ParticleGeneratorGroup(const std::vector<std::shared_ptr<ParticlesGenerator>>& generators);
    ParticleGeneratorGroup(const std::shared_ptr<ParticlesGenerator>& generator);
    
    
    std::vector<std::shared_ptr<ParticlesGenerator>> _generators;
};
