#include <2d/CCScene.h>
#include "TestScene.h"
#include "HeadUpDisplay.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/Environment.h"
#include "GUI/ViewPort.h"
#include "GUI/Image.h"
#include "GUI/Button.h"
#include "GUI/BoxLayout.h"
//#include "IGame.h"
#include "IUpdatable.h"
#include "GenericScene.h"

USING_NS_CC;

HeadUpDisplay::HeadUpDisplay(GenericScene* scene) : gui::ViewPort(scene)
{
    _scene = scene;
    
    _pauseButton = gui::Button::create("resources/button-pause-normal.png", "resources/button-pause-pressed.png");
    addView(_pauseButton);
    _pauseButton->setMargin(5, 5, 5, 5);
    _pauseButton->setCallback(std::bind(&HeadUpDisplay::onPauseClicked, this, std::placeholders::_1));
    
    Vec2 pausePos;
    pausePos.x = Convert::toPixels(Environment::getScreenSize().x) - _pauseButton->getSize().x;
    pausePos.y = Convert::toPixels(Environment::getScreenSize().y) - _pauseButton->getSize().y;
    _pauseButton->setPosition(pausePos);
}

HeadUpDisplay::~HeadUpDisplay()
{

}

void HeadUpDisplay::update(float delta)
{

}

void HeadUpDisplay::onPauseClicked(gui::Button * sender)
{
	// just for testing:
	_scene->setPaused(true);
	sender->setVisible(false);
	createPauseMenu();
}


void HeadUpDisplay::onContinueClicked(gui::Button* sender) 
{
	_scene->setPaused(false);
	_pauseMenu->setVisible(false);
	_pauseButton->setVisible(true);
}

void HeadUpDisplay::onRestartClicked(gui::Button* sender)
{
    auto manager = SceneManager::getInstance();
    manager->startGame();
}

/*
void HeadUpDisplay::setGameLayer(IGame* gameLayer)
{
	_gameLayer = gameLayer;
}
*/

void HeadUpDisplay::createPauseMenu()
{
	const std::shared_ptr<gui::Image> pauseMenu = gui::Image::create("resources/pause_menu_background.png", gui::ScalePolicy::Stretch);
	addView(pauseMenu);
	pauseMenu->setSize(cocos2d::Size(500, 500));

	/*
	const std::shared_ptr<gui::Image> decoreImage = gui::Image::create("pause_menu_decore.png", gui::ScalePolicy::Stretch);
	_viewPort->addView(decoreImage);
	decoreImage->setSize(cocos2d::Size(55, 400));
	*/
	
	std::shared_ptr<gui::Button> quitButton = gui::Button::create("resources/quit_button_normal.png", "resources/quit_button_pressed.png");
	pauseMenu->addView(quitButton);
	quitButton->setMargin(0, 0, 70, 0);
	quitButton->setCallback(std::bind(&HeadUpDisplay::onContinueClicked, this, std::placeholders::_1));

	std::shared_ptr<gui::Button> menuButton = gui::Button::create("resources/menu_button_normal.png", "resources/menu_button_pressed.png");
	pauseMenu->addView(menuButton);
	menuButton->setMargin(0, 0, 0, 0);
	menuButton->setCallback(std::bind(&HeadUpDisplay::onContinueClicked, this, std::placeholders::_1));

	std::shared_ptr<gui::Button> settingsButton = gui::Button::create("resources/settings_button_normal.png", "resources/settings_button_pressed.png");
	pauseMenu->addView(settingsButton);
	settingsButton->setMargin(0, 0, 0, 0);
	settingsButton->setCallback(std::bind(&HeadUpDisplay::onContinueClicked, this, std::placeholders::_1));

	std::shared_ptr<gui::Button> restartButton = gui::Button::create("resources/restart_button_normal.png", "resources/restart_button_pressed.png");
	pauseMenu->addView(restartButton);
	restartButton->setMargin(0, 0, 0, 0);
	restartButton->setCallback(std::bind(&HeadUpDisplay::onRestartClicked, this, std::placeholders::_1));

	std::shared_ptr<gui::Button> continueButton = gui::Button::create("resources/continue_button_normal.png", "resources/continue_button_pressed.png");
	pauseMenu->addView(continueButton);
	continueButton->setMargin(0, 0, 0, 30);
	continueButton->setCallback(std::bind(&HeadUpDisplay::onContinueClicked, this, std::placeholders::_1));

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
