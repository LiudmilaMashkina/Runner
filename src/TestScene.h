#pragma once

#pragma warning(push, 0)
#include <2d/CCScene.h>
#include <2d/CCSprite.h>
#include <platform/CCPlatformMacros.h>
#include <Box2D/Box2D.h>
#pragma warning(pop)

#include "Utils/MacroCreate.h"
#include "Utils/TimeProvider.h"

class GameWorld;
class GameCamera;
class GameLevelGenerator;
class IGameObject;
class ParticlesLayer;
class ParticlesSystem;

class TestScene : public cocos2d::Scene
{
public:
	CC_CREATE_FUNC(TestScene);

    virtual bool init() override;
	void update(float delta) override;
    bool shouldBeRemoved(std::shared_ptr<IGameObject> obj);

private:
	TestScene() {}
    cocos2d::Sprite* createBackground(const std::string & backgroundName);

	std::shared_ptr<GameWorld> _world;
    std::shared_ptr<GameCamera> _camera;
    std::shared_ptr<GameLevelGenerator> _generator;
    std::shared_ptr<TimeProvider> _timeProvider;
    ParticlesSystem* _system;

    b2Vec2 _winSize = {0.0f, 0.0f};
};
 
