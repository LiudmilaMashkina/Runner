#pragma once

#pragma warning(push, 0)
#include <2d/CCScene.h>
#include <2d/CCSprite.h>
#include <platform/CCPlatformMacros.h>
#include <Box2D/Box2D.h>
#pragma warning(pop)

#include "Utils/MacroCreate.h"
#include "Utils/TimeProvider.h"
#include "Utils/StrongPtr.h"
#include "Particles/ParticlesFactory.h"
#include "GenericScene.h"

class GameWorld;
class GameCamera;
class GameLevelGenerator;
class IGameObject;
class ParticlesLayer;
class ParticlesSystem;
class Hero;
class HeadUpDisplay;
class DropController;

class GameScene : public GenericScene
{
public:
	CC_CREATE_FUNC(GameScene, init);

    virtual bool init() override;
	void update(float delta) override;
    bool shouldBeRemoved(std::shared_ptr<IGameObject> obj);
    
    virtual ~GameScene();

private:
    GameScene();
    cocos2d::Sprite* createBackground(const std::string & backgroundName);
    cocos2d::Sprite* createSecondPlan(const std::string& planName, float ratioToScreenSize);
    
    cocos2d::Node* _gameNode = nullptr;
	std::shared_ptr<GameWorld> _world;
    std::shared_ptr<Hero> _hero;
    std::shared_ptr<GameCamera> _camera;
    std::shared_ptr<GameLevelGenerator> _levelGenerator;
    std::shared_ptr<TimeProvider> _timeProvider;
    StrongPtr<HeadUpDisplay> _hud;
    ParticlesFactory::ParticleSystemControls _particlesSystem;
    cocos2d::Sprite* _background = nullptr;
    cocos2d::Sprite* _backgroundTrees = nullptr;
    std::shared_ptr<DropController> _dropController;
    
    b2Vec2 _winSize = {0.0f, 0.0f};
    bool _isDeathMenu = false;
};
 
