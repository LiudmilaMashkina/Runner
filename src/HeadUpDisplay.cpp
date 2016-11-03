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
#include "GUI/View.h"
#include "GUI/CheckBox.h"
#include "GUI/ProgressBar.h"
#include "GUI/Label.h"
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
    
    _progressBar = gui::ProgressBar::create("resources/life_bar_base.png", "resources/life_bar_progress.png");
    addView(_progressBar);
    Vec2 progressPos;
    progressPos.x = 0.0f;
    progressPos.y = Convert::toPixels(Environment::getScreenSize().y) - _progressBar->getSize().y;
    _progressBar->setPosition(progressPos);
    
    _distanceBar = gui::Label::create("resources/dist_bar.png", "0", "resources/Monster_AG.ttf", 65);
    addView(_distanceBar);
    Vec2 distPos;
    distPos.x = progressPos.x + _progressBar->getSize().x;
    distPos.y = progressPos.y;
    _distanceBar->setPosition(distPos);
    //_distanceBar->setDistance(1);
}

HeadUpDisplay::~HeadUpDisplay()
{

}

void HeadUpDisplay::update(float delta)
{

}

void HeadUpDisplay::onPauseClicked(gui::Button * sender)
{
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
    manager->showGameScene();
}

void HeadUpDisplay::onMainMenuClicked(gui::Button *sender)
{
    auto manager = SceneManager::getInstance();
    manager->showMainMenu();
}

void HeadUpDisplay::setDistance(int dist)
{
    assert(_distanceBar);
    _distanceBar->setDistance(dist);
}

void HeadUpDisplay::setLifes(int lifes)
{
    assert(_progressBar);
    _progressBar->setLifes(lifes);
}

void HeadUpDisplay::createPauseMenu()
{
	const std::shared_ptr<gui::Image> pauseMenu = gui::Image::create("resources/pause_menu_background.png", gui::ScalePolicy::Stretch);
	addView(pauseMenu);
	pauseMenu->setSize(cocos2d::Size(500, 500));
	
	std::shared_ptr<gui::Button> menuButton = gui::Button::create("resources/menu_button_normal.png", "resources/menu_button_pressed.png");
	pauseMenu->addView(menuButton);
	menuButton->setMargin(0, 0, 0, 0);
	menuButton->setCallback(std::bind(&HeadUpDisplay::onMainMenuClicked, this, std::placeholders::_1));

    // adding sound buttons
    std::shared_ptr<gui::View> settingsButtons = gui::View::create();
    auto settingsLayout = gui::BoxLayout::create(gui::Orientation::Horizontal, gui::Alignment::Center);
    settingsButtons->setLayout(settingsLayout);
    auto soundOff = gui::CheckBox::create("resources/check_box_on.png", "resources/check_box_off.png");
    auto musicOff = gui::CheckBox::create("resources/music_check_box_on.png", "resources/music_check_box_off.png");
    settingsButtons->addView(soundOff);
    settingsButtons->addView(musicOff);
    settingsLayout->doLayout(settingsButtons, false);
    pauseMenu->addView(settingsButtons);
    // end
    
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


