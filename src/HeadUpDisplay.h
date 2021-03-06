 #pragma once

#include "GUI/ViewPort.h"
#include "SceneManager.h"
#include "Utils/MacroCreate.h"
#include "Utils/StrongPtr.h"

namespace gui
{
    class ProgressBar;
    class Button;
    class Label;
}

namespace gui2
{
    class Button;
    class ProgressBar;
}

class GenericScene;
class PauseMenu;

class HeadUpDisplay : public cocos2d::Node
{
public:
    HeadUpDisplay();
	virtual ~HeadUpDisplay();
	virtual void update(float delta);
	void onPauseClicked(gui2::Button* sender);
	void onContinueClicked();
	void onRestartClicked();
    void onMainMenuClicked();
    
    void setDistance(int dist);
    void setLifes(int lifes);
    void setCoins(int coins);
    
    void createDeathMenu(int distance, int coins);

	CC_CREATE_FUNC_1(HeadUpDisplay, initWithScene,
                     GenericScene*, scene);

private:
    bool initWithScene(GenericScene* scene);
    
    void createPauseButton(float scale, float winOffset);
    void createLifesBar(float scale, float winOffset);
    void createDistanceLabel(float scale, float horizontalOffset, float winOffset);
    void createCoinsLabel(float scale, float horizontalOffset, float winOffset);
    
    StrongPtr<gui2::Button> _pauseButton;
    StrongPtr<PauseMenu> _pauseMenu;
    StrongPtr<gui2::ProgressBar> _livesBar;
    StrongPtr<cocos2d::Label> _distanceLabel;
    StrongPtr<cocos2d::Label> _coinsLabel;
    GenericScene* _scene = nullptr;
};
