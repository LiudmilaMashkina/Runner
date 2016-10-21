#pragma warning(push, 0)
#include <2d/CCSprite.h>
#include <base/CCDirector.h>
#include <base/CCEventListenerTouch.h>
#include <base/CCEventDispatcher.h>
#pragma warning(pop)

#include "SceneBuilder.h"
#include "GameWorld.h"
#include "IUpdatable.h"
#include "GenericScene.h"
#include "GameCamera.h"
#include "UpdaterFunc.h"
#include "Utils/Environment.h"
#include "Utils/TimeProvider.h"
#include "Utils/Convert.h"
#include "GameObjects/GameLevelGenerator.h"
#include "GameObjects/IGameLavelInfo.h"
#include "Particles/ParticlesSystem.h"
#include "Particles/ParticlesGenerator.h"
#include "Hero/Hero.h"

USING_NS_CC;

SceneBuilder::SceneBuilder()
{
    _gameNode = Node::create();
    _timeProvider = TimeProvider::create();
}

SceneBuilder& SceneBuilder::withBackground()
{
    _background = Sprite::create("resources/background_square_256x256.png");
    Vec2 backgroundScale;
    backgroundScale.x = Convert::toPixels(Environment::getScreenSize().x) * 2 / _background->getContentSize().width;
    backgroundScale.y = Convert::toPixels(Environment::getScreenSize().y) * 2/ _background->getContentSize().height;
    _background->setScale(backgroundScale.x, backgroundScale.y);
    _background->setAnchorPoint(Vec2(0, 0));
    
    return *this;
}

SceneBuilder& SceneBuilder::withParticleLayer()
{
    _particlesSystem = ParticlesFactory::createGameParticlesSystem(_timeProvider);
    
    return *this;
}

SceneBuilder& SceneBuilder::withGameWorld()
{
    _world = std::shared_ptr<GameWorld>(new GameWorld(b2Vec2(0, -10), _gameNode));
    
    return *this;
}

SceneBuilder& SceneBuilder::withHero()
{
    assert(_levelGenerator);
    assert(_gameNode);
    assert(_world);
    
    _hero = Hero::create(_levelGenerator.get(), _gameNode, _world.get());
    _hero->setPosition({10, 10});
    _world->addObject(_hero);
    
    return *this;
}

SceneBuilder& SceneBuilder::withCamera()
{
    _camera = GameCamera::create();
    
    return *this;
}

SceneBuilder& SceneBuilder::withLevelGenerator()
{
    assert(_world);
    _levelGenerator = GameLevelGenerator::create(_world.get());
    _levelGenerator->generateUntil(Environment::getScreenSize().x * 0.75f);
    
    return *this;
}

GenericScene* SceneBuilder::build()
{
    GenericScene* scene = GenericScene::create();
    
    if (_background)
        scene->addChild(_background);
    
    if (_particlesSystem.particlesNode)
    {
        scene->addChild(_particlesSystem.particlesNode);
        scene->addUpdatable(_particlesSystem.particlesSystem);
    }
    
    scene->addChild(_gameNode);
    scene->addUpdatable(_timeProvider);
    
    if (_world)
        scene->addUpdatable(_world);
    
    if (_camera)
    {
        if (_background)
        {
            GameCamera::LayerInfo backgroundLayer;
            backgroundLayer.layer = _background;
            backgroundLayer.speedFactor = 0.3f;
            backgroundLayer.zoomFactor = 0.3f;
            backgroundLayer.clamp = true;
            _camera->addLayer(backgroundLayer);
        }
        
        auto camera = _camera;
        
        if (_particlesSystem.particlesNode)
        {
            GameCamera::LayerInfo particlesLayer;
            particlesLayer.layer = _particlesSystem.particlesNode;
            particlesLayer.speedFactor = 0.5f;
            particlesLayer.zoomFactor = 0.5f;
            particlesLayer.clamp = false;
            _camera->addLayer(particlesLayer);
            
            auto particlesSystem = _particlesSystem;
            //auto pGenerator = _particlesSystem.particlesGenerator;
            auto moveParticlesGenerator = [=](float delta)
            {
                b2Vec2 gPos;
                gPos.x = Environment::getScreenSize().x / 2.0f;
                gPos.y = -0.5f;
                Vec2 tmpPos = particlesSystem.particlesNode->convertToNodeSpace(Convert::toPixels(gPos));
                gPos = Convert::toMeters(tmpPos);
                particlesSystem.particlesGenerator->setPosition(gPos);
            };
            scene->addUpdatable(UpdaterFunc::create(moveParticlesGenerator));
        }
        
        GameCamera::LayerInfo gameLayer;
        gameLayer.layer = _gameNode;
        gameLayer.speedFactor = 1.0f;
        gameLayer.zoomFactor = 1.0f;
        gameLayer.clamp = false;
        _camera->addLayer(gameLayer);
        
        auto timeProvider = _timeProvider;
        
        if (_hero)
        {
            auto hero = _hero;
            auto moveCamera = [=](float delta)
            {
                b2Vec2 heroPos = hero->getPosition();
                b2Vec2 camPos;
                camPos.x = heroPos.x - Environment::getScreenSize().x / 3;
                camPos.y = heroPos.y - Environment::getScreenSize().y / 2;
                camera->setPosition(b2Vec2(camPos));
            };
            scene->addUpdatable(UpdaterFunc::create(moveCamera));
        }
        else
        {
            auto moveCamera = [=](float delta)
            {
                b2Vec2 camPos = {timeProvider->getTime() * 2, 0};
                camera->setPosition(b2Vec2(camPos));
            };
            scene->addUpdatable(UpdaterFunc::create(moveCamera));

        }
        
        auto levelGenerator = _levelGenerator;
        auto sync = [=](float delta)
        {
            float camX = camera->getPosition().x;
            float winSizeX = Environment::getScreenSize().x;
            levelGenerator->generateUntil(camX + winSizeX * 0.75f);
        };
        scene->addUpdatable(UpdaterFunc::create(sync));
    }
    
    if (_hero)
    {
        auto hero = _hero;
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = [=](Touch* touch, Event* event)
        {
            hero->onTap();
            return true;
        };
        scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, scene);
    }
    
    return scene;
}