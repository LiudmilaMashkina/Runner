 #pragma once

#include <2d/CCLayer.h>
#include "GUI/ViewPort.h"
#include "SceneManager.h"
#include "Utils/MacroCreate.h"

namespace gui
{
    class ProgressBar;
    class Button;
    class Label;
}

class GenericScene;

class HeadUpDisplay : public gui::ViewPort
{
public:
	virtual ~HeadUpDisplay();
	virtual void update(float delta);
	void onPauseClicked(gui::Button* sender);
	void onContinueClicked(gui::Button* sender);
	void onRestartClicked(gui::Button* sender);
    void onMainMenuClicked(gui::Button* sender);
    
    void setDistance(int dist);
    void setLifes(int lifes);
    void setCoins(int coins);
    
    void createDeathMenu(int distance, int coins);

	CREATE_FUNC_1(HeadUpDisplay, GenericScene*, scene);

private:
    HeadUpDisplay(GenericScene* scene);
    
    //void createStatsMenu();
    void createPauseMenu();
    
	std::shared_ptr<gui::Button> _pauseButton;
	std::shared_ptr<gui::View> _pauseMenu;
    std::shared_ptr<gui::ProgressBar> _progressBar;
    std::shared_ptr<gui::Label> _distanceBar;
    std::shared_ptr<gui::Label> _coinsBar;
    GenericScene* _scene = nullptr;
};
