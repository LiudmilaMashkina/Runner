#pragma once

#include "IGameObject.h"
#include "Particles/ParticlesGenerator.h"
#include "Particles/ParticlesFactory.h"
#include "Utils/MacroCreate.h"

class GameWorld;
class ParticlesSystem;


class ParticlesObject : public IGameObject
{
public:
    CREATE_FUNC_2(ParticlesObject, const ParticlesFactory::GeneratorInfo&, particlesSystem, GameWorld*, world);
    
    virtual ~ParticlesObject();
  
    virtual void update(float delta) override;
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override;
    virtual b2Body* getBody() override { return nullptr; }
    
    void setPaused(bool paused);
    void setPosition(const b2Vec2& pos);
    
    void shouldBeRemovedOnZeroParticles(bool removeOnZeroParticles) { _removeOnZeroParticles = removeOnZeroParticles; }
    
private:
    ParticlesObject(const ParticlesFactory::GeneratorInfo& particleSystem,
                    GameWorld* world);
    
    ParticlesFactory::GeneratorInfo _particleSystem;
    GameWorld* _world = nullptr;
    bool _removeOnZeroParticles = false;
};

 
