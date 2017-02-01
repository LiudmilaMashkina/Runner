#pragma once

#include <2d/CCScene.h>
#include <2d/CCSprite.h>
#include <Box2D/Box2D.h>
#include "Particles/ParticlesFactory.h"
#include "GenericScene.h"
#include "AnimationEngine/IAnimation.h"

class TimeProvider;
class ParticlesSystem;
class ForceFieldDebugDraw;

namespace gui2
{
    class CheckBox;
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
    void createGrass(cocos2d::Vec2 startPos, float untilX, float scale);
    void createNorthLights(const cocos2d::Vec2& winSize);
    
    static void turnOnCheckBox(gui2::CheckBox* checkBox);
    static void turnOffCheckBox(gui2::CheckBox* checkBox);
    cocos2d::Sprite* createFire(float scale);


	//std::shared_ptr<gui::ViewPort> _viewPort;
};
