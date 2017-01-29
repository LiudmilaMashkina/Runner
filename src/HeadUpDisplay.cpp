#include <2d/CCScene.h>
#include <2d/CCAction.h>
#include <2d/CCActionEase.h>
#include "TestScene.h"
#include "HeadUpDisplay.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/Environment.h"
#include "Utils/NodeUtils.h"
#include "GUI/ViewPort.h"
#include "GUI/Image.h"
#include "GUI/Button.h"
#include "GUI2/Button.h"
#include "GUI2/CheckBox.h"
#include "GUI/BoxLayout.h"
#include "GUI/View.h"
#include "GUI/CheckBox.h"
#include "GUI/ProgressBar.h"
#include "GUI/Label.h"
#include "IUpdatable.h"
#include "GenericScene.h"
#include "PauseMenu.h"


USING_NS_CC;

HeadUpDisplay::HeadUpDisplay()
{
    
}

bool HeadUpDisplay::initWithScene(GenericScene* scene)
{
    if (!Node::init())
        return false;
        
    _scene = scene;
    
    _pauseButton.reset(gui2::Button::create("resources/button-pause-normal.png",
                                            "resources/button-pause-pressed.png"));
    addChild(_pauseButton.get());
    _pauseButton->setAnchorPoint({1, 1});
    _pauseButton->setPosition(Convert::toPixels(Environment::getScreenSize()));
    _pauseButton->setCallback(std::bind(&HeadUpDisplay::onPauseClicked, this, std::placeholders::_1));
    
    
    /*
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
    
    _coinsBar = gui::Label::create("resources/coins_bar.png", "0", "resources/Monster_AG.ttf", 65);
    addView(_coinsBar);
    Vec2 coinsPos = distPos;
    coinsPos.x += _distanceBar->getSize().x;
    _coinsBar->setPosition(coinsPos);
    */
     
    return true;
}

HeadUpDisplay::~HeadUpDisplay()
{

}

void HeadUpDisplay::update(float delta)
{

}

void HeadUpDisplay::onPauseClicked(gui2::Button *sender)
{
	_scene->setPaused(true);
	sender->setVisible(false);
    
    assert(!_pauseMenu);
    _pauseMenu.reset(PauseMenu::create(this));
    addChild(_pauseMenu.get());
}


void HeadUpDisplay::onContinueClicked()
{
	_scene->setPaused(false);
    _pauseMenu->removeFromParentAndCleanup(true);
    _pauseMenu.reset();
	_pauseButton->setVisible(true);
}

void HeadUpDisplay::onRestartClicked()
{
    auto manager = SceneManager::getInstance();
    manager->showGameScene();
}

void HeadUpDisplay::onMainMenuClicked()
{
    auto manager = SceneManager::getInstance();
    manager->showMainMenu();
}

void HeadUpDisplay::setDistance(int dist)
{
//    assert(_distanceBar);
//    _distanceBar->setNum(dist);
}

void HeadUpDisplay::setLifes(int lifes)
{
//    assert(_progressBar);
//    _progressBar->setLifes(lifes);
}

void HeadUpDisplay::setCoins(int coins)
{
//    assert(_coinsBar);
//    _coinsBar->setNum(coins);
}

void HeadUpDisplay::createDeathMenu(int distance, int coins)
{
    /*
    const std::shared_ptr<gui::Image> deathMenu = gui::Image::create("resources/pause_menu_background.png", gui::ScalePolicy::Stretch);
    addView(deathMenu);
    deathMenu->setSize(cocos2d::Size(500, 500));
    
    auto verticalLayout = gui::BoxLayout::create(gui::Orientation::Vertical, gui::Alignment::Center);
    deathMenu->setLayout(verticalLayout);
    
    // buttons
    std::shared_ptr<gui::View> buttons = gui::View::create();
    auto horizotalLayout = gui::BoxLayout::create(gui::Orientation::Horizontal, gui::Alignment::Center);
    buttons->setLayout(horizotalLayout);
    
    std::shared_ptr<gui::Button> menuButton = gui::Button::create("resources/menu_button_normal.png", "resources/menu_button_pressed.png");
    buttons->addView(menuButton);
    menuButton->setMargin(0, 20, 0, 0);
    menuButton->setCallback(std::bind(&HeadUpDisplay::onMainMenuClicked, this, std::placeholders::_1));
    
    std::shared_ptr<gui::Button> restartButton = gui::Button::create("resources/restart_button_normal.png", "resources/restart_button_pressed.png");
    buttons->addView(restartButton);
    restartButton->setMargin(0, 0, 0, 0);
    restartButton->setCallback(std::bind(&HeadUpDisplay::onRestartClicked, this, std::placeholders::_1));
    
    horizotalLayout->doLayout(buttons, false);
    buttons->setMargin(30, 30, 30, 30);
    
    deathMenu->addView(buttons);
    
    
    //distance
    std::shared_ptr<gui::View> dist = gui::View::create();
    auto distHorizotalLayout = gui::BoxLayout::create(gui::Orientation::Horizontal, gui::Alignment::Center);
    dist->setLayout(distHorizotalLayout);
   
    auto distHeader = gui::Label::create("resources/dist_bar.png", "DISTANCE:", "resources/Monster_AG.ttf", 30);
    dist->addView(distHeader);
    distHeader->setMargin(0, 20, 0, 0);
    
    auto distValue = gui::Label::create("resources/dist_bar.png", std::to_string(distance), "resources/Monster_AG.ttf", 45);
    dist->addView(distValue);
    distValue->setMargin(0, 0, 0, 0);
    
    distHorizotalLayout->doLayout(dist, false);
    dist->setMargin(30, 30, 30, 30);
    
    deathMenu->addView(dist);
    
    //coins
    std::shared_ptr<gui::View> co = gui::View::create();
    auto coinsHorizotalLayout = gui::BoxLayout::create(gui::Orientation::Horizontal, gui::Alignment::Center);
    co->setLayout(coinsHorizotalLayout);
    
    auto coinsHeader = gui::Label::create("resources/dist_bar.png", "COINS:", "resources/Monster_AG.ttf", 40);
    co->addView(coinsHeader);
    coinsHeader->setMargin(0, 20, 0, 0);
    
    auto coinsValue = gui::Label::create("resources/dist_bar.png", std::to_string(coins), "resources/Monster_AG.ttf", 45);
    co->addView(coinsValue);
    distValue->setMargin(0, 0, 0, 0);
    
    coinsHorizotalLayout->doLayout(co, false);
    co->setMargin(30, 30, 30, 30);
    
    deathMenu->addView(co);
    
    verticalLayout->doLayout(deathMenu, false);
    
    Vec2 menuPos;
    menuPos.x = Convert::toPixels(Environment::getScreenSize().x / 2) - deathMenu->getSize().x / 2;
    menuPos.y = Convert::toPixels(Environment::getScreenSize().y / 2) - deathMenu->getSize().y / 2;
    deathMenu->setPosition(menuPos);
     */
}


