#pragma once

#include <2d/CCScene.h>
#include <2d/CCSprite.h>
#include <Box2D/Box2D.h>
#include "Particles/ParticlesFactory.h"
#include "GenericScene.h"

class TimeProvider;
class ParticlesSystem;
class ForceFieldDebugDraw;
namespace gui {
    class BoxLayout;
    class ViewPort;
}

class MainMenuScene : public GenericScene
{
public:
	virtual ~MainMenuScene();

	virtual bool init() override;
	CC_CREATE_FUNC(MainMenuScene, init);

private:
    MainMenuScene();
    
	cocos2d::Sprite* createBackground(const std::string & backgroundName);

	//ForceFieldDebugDraw* _forceDebugDraw;
//    gui::BoxLayout* _layout;
    std::shared_ptr<gui::ViewPort> _viewPort;
};
