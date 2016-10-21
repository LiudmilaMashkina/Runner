#pragma once

#include <2d/CCLayer.h>
#include "GUI/ViewPort.h"
#include "GUI/Button.h"
#include "SceneManager.h"
#include "Utils/MacroCreate.h"
#include "IGame.h"

class UILayer : public cocos2d::Node
{
public:
	virtual ~UILayer();
	virtual bool init() override;
	virtual void update(float delta) override;
	void onPauseClicked(gui::Button* sender);
	void onContinueClicked(gui::Button* sender);
	void onRestartClicked(gui::Button* sender);
	void setGameLayer(IGame* gameLayer);
	
	//CREATE_FUNC(UILayer);
	CC_CREATE_FUNC(UILayer, init);

private:
	void createPauseMenu();
	std::shared_ptr<gui::ViewPort> _viewPort;
	IGame* _gameLayer;
	std::shared_ptr<gui::Button> _pauseButton;
	std::shared_ptr<gui::View> _pauseMenu;
};
