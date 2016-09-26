#pragma once

#pragma warning(push, 0)
#include <2d/CCScene.h>
#include <platform/CCPlatformMacros.h>
#pragma warning(pop)

#include "Utils/MacroCreate.h"

class GameWorld;

class TestScene : public cocos2d::Scene
{
public:
	CC_CREATE_FUNC(TestScene);

    virtual bool init() override;
	void update(float delta) override;

private:
	TestScene() {}

	std::shared_ptr<GameWorld> _world;
};
 