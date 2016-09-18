#ifndef __TestScene__
#define __TestScene__

#pragma warning(push, 0)
#include <2d/CCScene.h>
#include <platform/CCPlatformMacros.h>
#pragma warning(pop)

#include "MacroCreate.h"

class TestScene : public cocos2d::Scene
{
public:
	CC_CREATE_FUNC(TestScene);

    virtual bool init() override;

private:
	TestScene() {}
};

#endif // __TestScene__
 