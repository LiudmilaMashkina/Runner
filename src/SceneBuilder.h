#pragma once

#include <memory>
#include <2d/CCNode.h>
#include "Particles/ParticlesFactory.h"

class GenericScene;
class IUpdatable;
class GameLevelGenerator;
class GameWorld;
class GameCamera;
class TimeProvider;
class ParticlesSystem;
class Hero;
class TouchHandler;
class SceneBuilder
{
public:
    SceneBuilder();
    
    SceneBuilder& withBackground();
    SceneBuilder& withParticleLayer();
    SceneBuilder& withGameWorld();
    SceneBuilder& withHero();
    SceneBuilder& withCamera();
    SceneBuilder& withLevelGenerator();
    
    GenericScene* build();

private:
    cocos2d::Node* _gameNode = nullptr;
    cocos2d::Sprite* _background = nullptr;
    std::shared_ptr<GameWorld> _world;
    std::shared_ptr<Hero> _hero;
    std::shared_ptr<GameCamera> _camera;
    std::shared_ptr<GameLevelGenerator> _levelGenerator;
    std::shared_ptr<TimeProvider> _timeProvider;
    ParticlesFactory::GeneratorInfo _particlesSystem;

};

