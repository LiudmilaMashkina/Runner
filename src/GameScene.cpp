#pragma warning(push, 0)
#include <base/CCDirector.h>
#pragma warning(pop)

#include "GameScene.h"
#include "GameWorld.h"
#include "Utils/Environment.h"
#include "Utils/Convert.h"
#include "ForceField/Clamper.h"
#include "Utils/b2Vec2Operators.h"
#include "ForceField/ForceFieldFactory.h"
#include "ForceField/GridForceField.h"
#include "ForceField/StaticForceField.h"
#include "ForceField/ForceFieldDebugDraw.h"
#include "B2DebugDraw/B2DebugDrawLayer.h"
#include "GameObjects/GameObjectComposer.h"
#include "GameObjects/GameLevelGenerator.h"
#include "Particles/ParticlesSystem.h"
#include "Particles/ParticlesGenerator.h"
#include "Particles/ParticlesMover.h"
#include "Particles/ParticlesReplacer.h"
#include "GameCamera.h"
#include "IUpdatable.h"
#include "Hero/Hero.h"
#include "HeadUpDisplay.h"
#include "UpdaterFunc.h"

USING_NS_CC;

bool GameScene::init()
{
	if (!GenericScene::init())
		return false;

    _winSize = Environment::getScreenSize();
    
    _background = createBackground("resources/background_square_256x256.png");
    addChild(_background);

    _gameNode = Node::create();
    addChild(_gameNode);
    
    _world = std::shared_ptr<GameWorld>(new GameWorld(b2Vec2(0, -10), _gameNode));
    addUpdatable(_world);
    
    _levelGenerator = GameLevelGenerator::create(_world.get());
    _levelGenerator->generateUntil(Environment::getScreenSize().x * 0.75f);
    
    _camera = GameCamera::create();
    
    _hero = Hero::create(_levelGenerator.get(), _gameNode, _world.get());
    _hero->setPosition({10, 10});
    _world->addObject(_hero);
    
    _timeProvider = TimeProvider::create();
    addUpdatable(_timeProvider);
    
    auto camera = _camera;
    auto timeProvider = _timeProvider;
    auto hero = _hero;
    auto moveCamera = [=](float delta)
    {
        b2Vec2 heroPos = hero->getPosition();
        b2Vec2 camPos;
        camPos.x = heroPos.x - Environment::getScreenSize().x / 3;
        camPos.y = heroPos.y - Environment::getScreenSize().y / 2;
        camera->setPosition(b2Vec2(camPos));
    };
    addUpdatable(UpdaterFunc::create(moveCamera));
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = [=](Touch* touch, Event* event)
    {
        hero->onTap();
        return true;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

    _particlesSystem = ParticlesFactory::createGameParticlesSystem(_timeProvider);
    addChild(_particlesSystem.particlesNode);
    addUpdatable(_particlesSystem.particlesSystem);
    
    auto particlesSystem = _particlesSystem;
    auto moveParticlesGenerator = [=](float delta)
    {
        b2Vec2 gPos;
        gPos.x = Environment::getScreenSize().x / 2.0f;
        gPos.y = -0.5f;
        Vec2 tmpPos = particlesSystem.particlesNode->convertToNodeSpace(Convert::toPixels(gPos));
        gPos = Convert::toMeters(tmpPos);
        particlesSystem.particlesGenerator->setPosition(gPos);
    };
    addUpdatable(UpdaterFunc::create(moveParticlesGenerator));
    
    auto levelGenerator = _levelGenerator;
    auto sync = [=](float delta)
    {
        float camX = camera->getPosition().x;
        float winSizeX = Environment::getScreenSize().x;
        levelGenerator->generateUntil(camX + winSizeX * 0.75f);
    };
    addUpdatable(UpdaterFunc::create(sync));
    
    
    GameCamera::LayerInfo backgroundLayer;
    backgroundLayer.layer = _background;
    backgroundLayer.speedFactor = 0.3f;
    backgroundLayer.zoomFactor = 0.3f;
    backgroundLayer.clamp = true;
    _camera->addLayer(backgroundLayer);

    GameCamera::LayerInfo particlesLayer;
    particlesLayer.layer = _particlesSystem.particlesNode;
    particlesLayer.speedFactor = 0.5f;
    particlesLayer.zoomFactor = 0.5f;
    particlesLayer.clamp = false;
    _camera->addLayer(particlesLayer);
    
    GameCamera::LayerInfo gameLayer;
    gameLayer.layer = _gameNode;
    gameLayer.speedFactor = 1.0f;
    gameLayer.zoomFactor = 1.0f;
    gameLayer.clamp = false;
    _camera->addLayer(gameLayer);
    
    _hud = HeadUpDisplay::create(this);
    
    
    auto physDebugDraw = B2DebugDrawLayer::create(_world->getPhysics().get(), Environment::getPTMratio());
	_gameNode->addChild(physDebugDraw, 100);

    return true;
}

void GameScene::update(float delta)
{
    GenericScene::update(delta);
    if (_hud && _hero)
    {
        int dist = _hero->getPosition().x;
        _hud->setDistance(dist);
        
        int lifes = _hero->getLifes();
        _hud->setLifes(lifes);  
    }
}

Sprite* GameScene::createBackground(const std::string & backgroundName)
{
    auto background = Sprite::create(backgroundName);
    
    Vec2 backgroundScale;
    backgroundScale.x = Convert::toPixels(_winSize.x) * 2 / background->getContentSize().width;
    backgroundScale.y = Convert::toPixels(_winSize.y) * 2/ background->getContentSize().height;
    background->setScale(backgroundScale.x, backgroundScale.y);
    background->setAnchorPoint(Vec2(0, 0));
    
    return background;
}

