#include <2d/CCScene.h>
#include <2d/CCAction.h>
#include <2d/CCActionEase.h>
#include <2d/CCLabel.h>
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
#include "GUI2/ProgressBar.h"
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
    
    auto winSize = Convert::toPixels(Environment::getScreenSize());
    
    _scene = scene;
    
    auto referenceTexture = TextureCache::getInstance()->addImage("resources/hud_lives_base.png");
    float uiScale = winSize.y * 0.13 / referenceTexture->getContentSize().height;
    float gap = winSize.y * 0.003;
    
    createPauseButton(uiScale);
    createLifesBar(uiScale);
    createDistanceLabel(uiScale, gap);
    createCoinsLabel(uiScale, gap);
    
    return true;
}

void HeadUpDisplay::createPauseButton(float scale)
{
    _pauseButton.reset(gui2::Button::create("resources/button-pause-normal.png",
                                            "resources/button-pause-pressed.png"));
    addChild(_pauseButton.get());
    _pauseButton->setAnchorPoint({1, 1});
    _pauseButton->setPosition(Convert::toPixels(Environment::getScreenSize()));
    _pauseButton->setScale(scale);
    _pauseButton->setCallback(std::bind(&HeadUpDisplay::onPauseClicked,
                                        this, std::placeholders::_1));
}

void HeadUpDisplay::createLifesBar(float scale)
{
    auto winSize = Convert::toPixels(Environment::getScreenSize());

    _livesBar.reset(gui2::ProgressBar::create("resources/hud_lives_base.png",
                                              "resources/hud_lives_filling.png"));
    addChild(_livesBar.get());
    auto outline = Sprite::create("resources/hud_lives_outline.png");
    outline->setPosition(Vec2(_livesBar->getContentSize()) / 2);
    _livesBar->addChild(outline);
    
    _livesBar->setScale(scale);
    _livesBar->setRotation(-90);
    _livesBar->setAnchorPoint({1, 1});
    _livesBar->setPosition(0, winSize.y);
    _livesBar->setScale(scale);
    setLifes(100);
}

void HeadUpDisplay::createDistanceLabel(float scale, float gap)
{
    auto winSize = Convert::toPixels(Environment::getScreenSize());

    auto distBase = Sprite::create("resources/hud_dist_coins_base.png");
    addChild(distBase);
    distBase->setScale(scale);
    distBase->setAnchorPoint({0, 1});
    distBase->setPosition(NodeUtils::getScaledSize(_livesBar.get()).x + gap, winSize.y);
    _distanceLabel.reset(Label::createWithTTF("0", "resources/Monster_AG.ttf", 65)); // TODO: change font size
    distBase->addChild(_distanceLabel.get());
    _distanceLabel->setAnchorPoint({0, 0.5});
    _distanceLabel->setPosition(distBase->getContentSize().width * 0.05,
                                distBase->getContentSize().height / 2);
    _distanceLabel->setColor(Color3B(139, 197, 63));
}

void HeadUpDisplay::createCoinsLabel(float scale, float gap)
{
    auto winSize = Convert::toPixels(Environment::getScreenSize());

    auto coinsBase = Sprite::create("resources/hud_dist_coins_base.png");
    addChild(coinsBase);
    coinsBase->setScale(scale);
    coinsBase->setAnchorPoint({0, 0});
    coinsBase->setPosition(NodeUtils::getScaledSize(_livesBar.get()).x + gap,
                           winSize.y - NodeUtils::getScaledSize(_livesBar.get()).y);
    
    auto coinsSign = Sprite::create("resources/hud_coin_sign.png");
    coinsBase->addChild(coinsSign);
    coinsSign->setAnchorPoint({0, 0.5});
    coinsSign->setPosition(coinsBase->getContentSize().width * 0.05,
                           coinsBase->getContentSize().height / 2);
    
    _coinsLabel.reset(Label::createWithTTF("0", "resources/Monster_AG.ttf", 65)); // TODO: change font size
    coinsBase->addChild(_coinsLabel.get());
    _coinsLabel->setAnchorPoint({0, 0.5});
    _coinsLabel->setPosition(coinsSign->getPosition().x + coinsSign->getContentSize().width, coinsBase->getContentSize().height / 2);
    _coinsLabel->setColor(Color3B(139, 197, 63));
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
    std::string text = std::to_string(dist);
    _distanceLabel->setString(text);
}

void HeadUpDisplay::setLifes(int lifes)
{
    if (lifes <= 25)
        _livesBar->setProgressColor(Color3B(200, 37, 44));
    else if (lifes <= 50)
        _livesBar->setProgressColor(Color3B(204, 126, 45));
    else if (lifes <= 75)
        _livesBar->setProgressColor(Color3B(212, 222, 37));
    else
        _livesBar->setProgressColor(Color3B(139, 197, 63));
    
    _livesBar->setProgress(lifes);
}

void HeadUpDisplay::setCoins(int coins)
{
    std::string text = std::to_string(coins);
    _coinsLabel->setString(text);
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


