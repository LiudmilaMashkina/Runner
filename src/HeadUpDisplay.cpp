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
#include "DeathMenu.h"


USING_NS_CC;

HeadUpDisplay::HeadUpDisplay()
{
    
}

bool HeadUpDisplay::initWithScene(GenericScene* scene)
{
    if (!Node::init())
        return false;
    
    auto winSize = Convert::toPixels(Environment::getScreenSize());
    float winOffset = winSize.x * 0.005;
    
    _scene = scene;
    
    auto livesTexture = TextureCache::getInstance()->addImage("rsrc/hud_lifes_base.png");
    auto labelBackgroundTexture = TextureCache::getInstance()->addImage("rsrc/hud_dist_coins_base.png");
    
    float uiScale = winSize.y * 0.13 / livesTexture->getContentSize().height;
    float horizontalOffset = uiScale * (livesTexture->getContentSize().height - labelBackgroundTexture->getContentSize().height * 2);
    
    createPauseButton(uiScale, winOffset);
    createLifesBar(uiScale, winOffset);
    createDistanceLabel(uiScale, horizontalOffset, winOffset);
    createCoinsLabel(uiScale, horizontalOffset, winOffset);
    
    return true;
}

void HeadUpDisplay::createPauseButton(float scale, float winOffset)
{
    _pauseButton.reset(gui2::Button::create("rsrc/hud_pause_button.png",
                                            "rsrc/hud_pause_button_pressed.png"));
    addChild(_pauseButton.get());
    _pauseButton->setAnchorPoint({1, 1});
    _pauseButton->setPosition(Convert::toPixels(Environment::getScreenSize()) - Vec2(winOffset, winOffset));
    _pauseButton->setScale(scale);
    _pauseButton->setCallback(std::bind(&HeadUpDisplay::onPauseClicked,
                                        this, std::placeholders::_1));
}

void HeadUpDisplay::createLifesBar(float scale, float winOffset)
{
    auto winSize = Convert::toPixels(Environment::getScreenSize());

    _livesBar.reset(gui2::ProgressBar::create("rsrc/hud_lifes_base.png",
                                              "rsrc/hud_lives_filling.png"));
    addChild(_livesBar.get());
    auto outline = Sprite::create("rsrc/hud_lives_outline.png");
    outline->setPosition(Vec2(_livesBar->getContentSize()) / 2);
    _livesBar->addChild(outline);
    
    _livesBar->setScale(scale);
    _livesBar->setRotation(-90);
    _livesBar->setAnchorPoint({1, 1});
    _livesBar->setPosition(winOffset, winSize.y - winOffset);
    _livesBar->setScale(scale);
    setLifes(100);
}

void HeadUpDisplay::createDistanceLabel(float scale, float horizontalOffset, float winOffset)
{
    auto winSize = Convert::toPixels(Environment::getScreenSize());

    auto distBase = Sprite::create("rsrc/hud_dist_coins_base.png");
    addChild(distBase);
    distBase->setScale(scale);
    distBase->setAnchorPoint({0, 1});
    distBase->setPosition(NodeUtils::getScaledSize(_livesBar.get()).x + horizontalOffset + winOffset, winSize.y - winOffset);
    _distanceLabel.reset(Label::createWithTTF("0", "rsrc/Monster_AG.ttf", 65)); // TODO: change font size
    distBase->addChild(_distanceLabel.get());
    _distanceLabel->setAnchorPoint({0, 0.5});
    _distanceLabel->setPosition(distBase->getContentSize().width * 0.05,
                                distBase->getContentSize().height / 2);
    _distanceLabel->setColor(Color3B(139, 197, 63));
}

void HeadUpDisplay::createCoinsLabel(float scale, float horizontalOffset, float winOffset)
{
    auto winSize = Convert::toPixels(Environment::getScreenSize());

    auto coinsBase = Sprite::create("rsrc/hud_dist_coins_base.png");
    addChild(coinsBase);
    coinsBase->setScale(scale);
    coinsBase->setAnchorPoint({0, 0});
    coinsBase->setPosition(NodeUtils::getScaledSize(_livesBar.get()).x + horizontalOffset + winOffset,
                           winSize.y - NodeUtils::getScaledSize(_livesBar.get()).y - winOffset);
    
    auto coinsSign = Sprite::create("rsrc/hud_coin_sign.png");
    coinsBase->addChild(coinsSign);
    coinsSign->setAnchorPoint({0, 0.5});
    coinsSign->setPosition(coinsBase->getContentSize().width * 0.05,
                           coinsBase->getContentSize().height / 2);
    
    _coinsLabel.reset(Label::createWithTTF("0", "rsrc/Monster_AG.ttf", 65)); // TODO: change font size
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
    _scene->setPaused(true);
    _pauseButton->setVisible(false);
    _livesBar->setVisible(false);
    _distanceLabel->getParent()->setVisible(false);
    _coinsLabel->getParent()->setVisible(false);
    addChild(DeathMenu::create(this, distance, coins));
}


