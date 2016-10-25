 #pragma once

#include <2d/CCLayer.h>
#include "GUI/ViewPort.h"
#include "GUI/Button.h"
#include "SceneManager.h"
#include "Utils/MacroCreate.h"
#include "IGame.h"
#include "GUI/ViewPort.h"

class GenericScene;

class HeadUpDisplay : public gui::ViewPort
{
public:
	virtual ~HeadUpDisplay();
	virtual void update(float delta);
	void onPauseClicked(gui::Button* sender);
	void onContinueClicked(gui::Button* sender);
	void onRestartClicked(gui::Button* sender);
	//void setGameLayer(IGame* gameLayer);
	
	CREATE_FUNC_1(HeadUpDisplay, GenericScene*, scene);

private:
    HeadUpDisplay(GenericScene* scene);
	
    void createPauseMenu();
	
    //IGame* _gameLayer;
	std::shared_ptr<gui::Button> _pauseButton;
	std::shared_ptr<gui::View> _pauseMenu;
    GenericScene* _scene = nullptr;
};
