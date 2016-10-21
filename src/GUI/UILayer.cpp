#include <2d/CCScene.h>
#include "TestScene.h"
#include "UILayer.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/Environment.h"
#include "GUI/ViewPort.h"
#include "GUI/Image.h"
#include "GUI/Button.h"
#include "GUI/BoxLayout.h"
#include "IGame.h"

USING_NS_CC;

/*
Scene* UILayer::createScene()
{
auto scene = Scene::create();
auto layer = UILayer::create();
scene->addChild(layer);
return scene;
}

*/

UILayer::~UILayer()
{

}

bool UILayer::init()
{
	if (!Node::init())
		return false;

	_viewPort = gui::ViewPort::create(this);

	_pauseButton = gui::Button::create("button-pause-normal.png", "button-pause-pressed.png");
	_viewPort->addView(_pauseButton);
	_pauseButton->setMargin(5, 5, 5, 5);
	_pauseButton->setCallback(std::bind(&UILayer::onPauseClicked, this, std::placeholders::_1));

	Vec2 pausePos;
	pausePos.x = Convert::toPixels(Environment::getScreenSize().x) - _pauseButton->getSize().x;
	pausePos.y = Convert::toPixels(Environment::getScreenSize().y) - _pauseButton->getSize().y;
	_pauseButton->setPosition(pausePos);
	
	scheduleUpdate();
	return true;
} 

void UILayer::update(float delta)
{

}

void UILayer::onPauseClicked(gui::Button * sender)
{
	// just for testing:
	_gameLayer->setPaused(true);
	sender->setVisible(false);
	createPauseMenu();
}

void UILayer::onContinueClicked(gui::Button* sender) 
{
	_gameLayer->setPaused(false);
	_pauseMenu->setVisible(false);
	_pauseButton->setVisible(true);
}

void UILayer::onRestartClicked(gui::Button* sender)
{
    auto manager = SceneManager::getInstance();
    manager->startGame();
}

void UILayer::setGameLayer(IGame* gameLayer)
{
	_gameLayer = gameLayer;
}

void UILayer::createPauseMenu()
{
	const std::shared_ptr<gui::Image> pauseMenu = gui::Image::create("pause_menu_background.png", gui::ScalePolicy::Stretch);
	_viewPort->addView(pauseMenu);
	pauseMenu->setSize(cocos2d::Size(500, 500));

	/*
	const std::shared_ptr<gui::Image> decoreImage = gui::Image::create("pause_menu_decore.png", gui::ScalePolicy::Stretch);
	_viewPort->addView(decoreImage);
	decoreImage->setSize(cocos2d::Size(55, 400));
	*/
	
	std::shared_ptr<gui::Button> quitButton = gui::Button::create("quit_button_normal.png", "quit_button_pressed.png");
	pauseMenu->addView(quitButton);
	quitButton->setMargin(0, 0, 70, 0);
	quitButton->setCallback(std::bind(&UILayer::onContinueClicked, this, std::placeholders::_1));

	std::shared_ptr<gui::Button> menuButton = gui::Button::create("menu_button_normal.png", "menu_button_pressed.png");
	pauseMenu->addView(menuButton);
	menuButton->setMargin(0, 0, 0, 0);
	menuButton->setCallback(std::bind(&UILayer::onContinueClicked, this, std::placeholders::_1));

	std::shared_ptr<gui::Button> settingsButton = gui::Button::create("settings_button_normal.png", "settings_button_pressed.png");
	pauseMenu->addView(settingsButton);
	settingsButton->setMargin(0, 0, 0, 0);
	settingsButton->setCallback(std::bind(&UILayer::onContinueClicked, this, std::placeholders::_1));

	std::shared_ptr<gui::Button> restartButton = gui::Button::create("restart_button_normal.png", "restart_button_pressed.png");
	pauseMenu->addView(restartButton);
	restartButton->setMargin(0, 0, 0, 0);
	restartButton->setCallback(std::bind(&UILayer::onRestartClicked, this, std::placeholders::_1));

	std::shared_ptr<gui::Button> continueButton = gui::Button::create("continue_button_normal.png", "continue_button_pressed.png");
	pauseMenu->addView(continueButton);
	continueButton->setMargin(0, 0, 0, 30);
	continueButton->setCallback(std::bind(&UILayer::onContinueClicked, this, std::placeholders::_1));

    std::shared_ptr<gui::ILayout> layout = gui::BoxLayout::create(gui::Orientation::Vertical, gui::Alignment::Center);
	pauseMenu->setLayout(layout);

	layout->doLayout(pauseMenu, true);

	Vec2 menuPos;
    menuPos.x = Convert::toPixels(Environment::getScreenSize().x / 2) - pauseMenu->getSize().x / 2;
	menuPos.y = Convert::toPixels(Environment::getScreenSize().y / 2) - pauseMenu->getSize().y / 2;
	pauseMenu->setPosition(menuPos);

	/*
	Vec2 decorPos;
	decorPos.x = GameUtils::convertToPixels(GameUtils::getScreenSize().x / 2) - decoreImage->getSize().width / 2;
	decorPos.y = GameUtils::convertToPixels(GameUtils::getScreenSize().y / 2) - decoreImage->getSize().height / 2;
	decoreImage->setPosition({ menuPos.x + 60, menuPos.y + 20 });
	*/
	_pauseMenu = pauseMenu;
}
