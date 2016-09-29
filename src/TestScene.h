#pragma once

#pragma warning(push, 0)
#include <2d/CCScene.h>
#include <platform/CCPlatformMacros.h>
#include <Box2D/Box2D.h>
#pragma warning(pop)

#include "Utils/MacroCreate.h"

class GameWorld;
class GameCamera;
class GameLevelGenerator;
class IGameObject;

class TestScene : public cocos2d::Scene
{
public:
	CC_CREATE_FUNC(TestScene);

    virtual bool init() override;
	void update(float delta) override;
    bool shouldBeRemoved(std::shared_ptr<IGameObject> obj);

private:
	TestScene() {}

	std::shared_ptr<GameWorld> _world;
    std::shared_ptr<GameCamera> _camera;
    std::shared_ptr<GameLevelGenerator> _generator;
    b2Vec2 _winSize = {0.0f, 0.0f};
};
 
