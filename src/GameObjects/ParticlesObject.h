#pragma once

#include "IGameObject.h"
#include "Particles/ParticlesGenerator.h"
#include "Particles/ParticlesFactory.h"

class GameWorld;
class ParticlesSystem;


class ParticlesObject : public IGameObject
{
public:
    ParticlesObject(const ParticlesFactory::GeneratorInfo& particleSystem,
                    GameWorld* world);
    virtual ~ParticlesObject();
  
    virtual void update(float delta) override;
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override;
    void setPaused(bool paused);
    
private:
    ParticlesFactory::GeneratorInfo _particleSystem;
    GameWorld* _world = nullptr;
};

 
