#pragma warning(push, 0)
#include <base/CCDirector.h>
#pragma warning(pop)

#include "TestScene.h"
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

USING_NS_CC;

bool TestScene::init()
{
    
	if (!Scene::init())
		return false;

    _winSize = Environment::getScreenSize();
    
    auto background = createBackground("resources/background_1_1024x1024.jpg");
    addChild(background);
    
    Node* gameNode = Node::create();
    addChild(gameNode);

    _timeProvider = TimeProvider::create();
    _world = std::shared_ptr<GameWorld>(new GameWorld(b2Vec2(0, -10), gameNode, _timeProvider));
    _generator = GameLevelGenerator::create(_world.get());
    
    b2Vec2 fieldSize = Environment::getScreenSize();
    auto forceField = ForceFieldFactory::createWindUpField(_timeProvider, fieldSize);
    //auto system = new ParticlesSystem();
    //_system = system;
    
    ParticlesGenerator::Params gParams;
    gParams.fileName = "resources/particle_16x16.png";
    gParams.rate = 5;
    gParams.velocityRange.set(b2Vec2(0, 1), b2Vec2(0, 2));
    gParams.massRange.set(0.5, 1);
    gParams.position = b2Vec2(Environment::getScreenSize().x / 2.0f, -0.5);
    gParams.generationRange.set(b2Vec2(-7.0f , 0.0f), b2Vec2(7.0f, 0.0f));
    gParams.field = forceField;

    auto pGenerator = ParticlesGenerator::create(gParams, this);
    _system->addSystemUpdater(pGenerator);

    auto pMover = ParticlesMover::create(forceField, 2);
    _system->addParticlesUpdater(pMover);
    
    auto pReplacer = ParticlesReplacer::create();
    
    ParticlesReplacer::Bounds bounds;
    bounds.downLeft = b2Vec2(0, 0);
    bounds.upperRight = Environment::getScreenSize();
    
    pReplacer->setBounds(bounds);
    std::vector<GameCamera::LayerInfo> layers;
    
    GameCamera::LayerInfo gameLayer;
    gameLayer.layer = gameNode;
    gameLayer.speedFactor = 1.0f;
    gameLayer.zoomFactor = 1.0f;
    layers.push_back(gameLayer);
    
    GameCamera::LayerInfo backgroundLayer;
    backgroundLayer.layer = background;
    backgroundLayer.speedFactor = 0.5f;
    backgroundLayer.zoomFactor = 0.5f;
    backgroundLayer.clamp = true;
    layers.push_back(backgroundLayer);
    
    auto physDebugDraw = B2DebugDrawLayer::create(_world->getPhysics().get(), Environment::getPTMratio());
	gameNode->addChild(physDebugDraw, 100);

    return true;
}

void TestScene::update(float delta)
{
    static float time = 0;
    time += delta;
    
	_world->update(delta);
    b2Vec2 camPos = {time * 2, 0};
    _camera->setPosition(b2Vec2(camPos));
    _generator->generateUntil(camPos.x + _winSize.x * 0.75f);
    
    auto shouldRemove = [&](const std::shared_ptr<IGameObject>& obj)
    {
        b2Vec2 objPos = obj->getPosition();
        if (objPos.x < camPos.x + 5)
            return true;
        return false;
    };
    
    _world->removeObject(shouldRemove);
    _timeProvider->update(delta);
    _system->update(delta);

}

Sprite* TestScene::createBackground(const std::string & backgroundName)
{
    auto background = Sprite::create(backgroundName);
    
    Vec2 backgroundScale;
    backgroundScale.x = Convert::toPixels(_winSize.x) * 2 / background->getContentSize().width;
    backgroundScale.y = Convert::toPixels(_winSize.y) * 2/ background->getContentSize().height;
    background->setScale(backgroundScale.x, backgroundScale.y);
    background->setAnchorPoint(Vec2(0, 0));
    
    return background;
}

