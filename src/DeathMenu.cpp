#include <2d/CCScene.h>
#include <2d/CCAction.h>
#include <2d/CCActionEase.h>
#include "HeadUpDisplay.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/Environment.h"
#include "Utils/NodeUtils.h"
#include "GUI2/CheckBox.h"
#include "GUI2/Button.h"
#include "DeathMenu.h"


USING_NS_CC;


namespace
{
    const float MenuMoveTime = 0.5;
    const float MenuEaseRate = 1;
    const float MenuCloseDelay = 0.2;
    const float BackgroundFadeTime = 0.5;
    const float EyesFadeTime = 0.4;
    const float EyesFadeDelay = 0.9;
}


DeathMenu::DeathMenu()
{
    
}

DeathMenu::~DeathMenu()
{
    
}

bool DeathMenu::initWithHud(HeadUpDisplay* hud, int distance, int coins)
{
    if (!Node::init())
        return false;
        
    _hud = hud;
    
    auto winSize = Convert::toPixels(Environment::getScreenSize());
    
    {
        auto background = Sprite::create("rsrc/deathmenu_background.png");
        addChild(background);
        background->setAnchorPoint({0, 0});
        background->setPosition(0, 0);
        NodeUtils::scaleTo(background, winSize);

        background->setOpacity(0);
        auto fade = EaseCubicActionIn::create(FadeTo::create(BackgroundFadeTime, 255));
        background->runAction(fade);
        
        // distance info label
        auto distLabelTitle = Label::createWithTTF("Distance:", "rsrc/Monster_AG.ttf", 65);
        background->addChild(distLabelTitle);
        distLabelTitle->setAnchorPoint({0, 0.5});
        //distLabelTitle->setPosition(winSize.x * 0.2, winSize.y * 0.7);
        distLabelTitle->setPosition(0, 0);
        distLabelTitle->setColor(Color3B(234, 222, 174));
        
        std::string dist = std::to_string(distance);
        auto distLabel = Label::createWithTTF(dist, "rsrc/Monster_AG.ttf", 65);
        background->addChild(distLabel);
        distLabel->setAnchorPoint({0, 0.5});
        auto distPos = distLabelTitle->getPosition();
        distPos.x += distLabelTitle->getContentSize().width + winSize.x * 0.02;
        distLabel->setPosition(distPos);
        distLabel->setColor(Color3B(234, 222, 174));
    }
    
    _deer = Sprite::create("rsrc/deathmenu_deer.png");
    addChild(_deer);
    _deer->setAnchorPoint({0.5, 0});
    _deer->setPosition(winSize.x / 2, -winSize.y * 0.75);
    Vec2 deerSize = _deer->getContentSize();
    float deerHeight = winSize.y * 0.7;
    float scale = deerHeight / deerSize.y;
    _deer->setScale(scale);
    auto move = EaseOut::create(MoveTo::create(MenuMoveTime, {winSize.x / 2, 0}), MenuEaseRate);
    _deer->runAction(move);
    
    auto deerScaledSize = NodeUtils::getScaledSize(_deer);
    
    {
        // restart button
        auto button = gui2::Button::create("rsrc/deathmenu_restart.png", "rsrc/deathmenu_restart_pressed.png");
        auto buttonScaledSIze = NodeUtils::getScaledSize(button);
        button->setAnchorPoint({1, 0});
        Vec2 pos;
        pos.x = 0.46;
        pos.y = 0.36;
        NodeUtils::attach(button, _deer, pos);
        button->setCallback(std::bind(&DeathMenu::onRestartClicked,
                                      this, std::placeholders::_1));
        // mein menu button
        auto mainMenuButton = gui2::Button::create("rsrc/deathmenu_mainmenu.png", "rsrc/deathmenu_mainmenu_pressed.png");
        auto mmButtonScaledSIze = NodeUtils::getScaledSize(button);
        mainMenuButton->setAnchorPoint({0, 0});
        Vec2 mmPos;
        mmPos.x = 0.54;
        mmPos.y = 0.36;
        NodeUtils::attach(mainMenuButton, _deer, mmPos);
        mainMenuButton->setCallback(std::bind(&DeathMenu::onMainMenuClicked,
                                      this, std::placeholders::_1));
        // eyes
        auto eyes = Sprite::create("rsrc/deathmenu_deer_eyes.png");
        NodeUtils::attach(eyes, _deer, {0.5, 0.37}, 1);
        
        eyes->setOpacity(0);
        auto delay = DelayTime::create(EyesFadeDelay);
        auto fade = EaseExponentialIn::create(FadeTo::create(EyesFadeTime, 255));
        auto sequence = Sequence::create(delay, fade, nullptr);
        eyes->runAction(sequence);
        
        // totem
        auto cat = Sprite::create("rsrc/deathmenu_cat.png");
        cat->setAnchorPoint({1, 0.18});
        NodeUtils::attach(cat, mainMenuButton, {0.67, 0.61}, 1);
        
        // eyes
        auto catEyes = Sprite::create("rsrc/deathmenu_cat_eyes.png");
        NodeUtils::attach(catEyes, cat, {0.5, 0.76}, 1);
        catEyes->setOpacity(0);
        {
            auto delay = DelayTime::create(EyesFadeDelay);
            auto fade = EaseExponentialIn::create(FadeTo::create(EyesFadeTime, 255));
            auto sequence = Sequence::create(delay, fade, nullptr);
            catEyes->runAction(sequence);
        }
    }
    
    
    
    
    /*
    //auto move = EaseElasticOut::create(MoveTo::create(MenuMoveTime, winSize / 2), MenuEaseRate);
    //_base->runAction(move);
    
    auto restartTexture = TextureCache::getInstance()->addImage("rsrc/deathmenu_restart.png");
    auto mainMenuTexture = TextureCache::getInstance()->addImage("rsrc/deathmenu_mainmenu.png");
    
    float horizontalGapSum = baseSize.x - (restartTexture->getContentSize().width + mainMenuTexture->getContentSize().width);
    float sideGap = horizontalGapSum * 0.4;
    
    {
        // restart button
        auto button = gui2::Button::create("rsrc/deathmenu_restart.png", "rsrc/deathmenu_restart_pressed.png");
        button->setAnchorPoint({0, 0});
        NodeUtils::attach(button, _base, {sideGap / baseSize.x, 0.05});
        button->setCallback(std::bind(&DeathMenu::onRestartClicked,
                                      this, std::placeholders::_1));
        // totem
        auto deer = Sprite::create("rsrc/deathmenu_deer.png");
        deer->setAnchorPoint({0, 0.125});
        NodeUtils::attach(deer, button, {0, 1}, 1);
        
        // eyes
        auto eyes = Sprite::create("rsrc/deathmenu_deer_eyes.png");
        NodeUtils::attach(eyes, deer, {0.5, 0.23}, 1);
        
        eyes->setOpacity(0);
        auto delay = DelayTime::create(EyesFadeDelay);
        auto fade = EaseExponentialIn::create(FadeTo::create(EyesFadeTime, 255));
        auto sequence = Sequence::create(delay, fade, nullptr);
        eyes->runAction(sequence);
    }
    
    {
        // main menu button
        auto button = gui2::Button::create("rsrc/deathmenu_mainmenu.png", "rsrc/deathmenu_mainmenu_pressed.png");
        button->setAnchorPoint({1, 0});
        NodeUtils::attach(button, _base, {1 - sideGap / baseSize.x, 0.05});
        button->setCallback(std::bind(&DeathMenu::onMainMenuClicked, this, std::placeholders::_1));
        
        // totem
        auto cat = Sprite::create("rsrc/deathmenu_cat.png");
        cat->setAnchorPoint({1, 0.18});
        NodeUtils::attach(cat, button, {0.9, 1}, 1);
        
        // eyes
        auto eyes = Sprite::create("rsrc/deathmenu_cat_eyes.png");
        NodeUtils::attach(eyes, cat, {0.5, 0.76}, 1);
        
        eyes->setOpacity(0);
        auto delay = DelayTime::create(EyesFadeDelay);
        auto fade = EaseExponentialIn::create(FadeTo::create(EyesFadeTime, 255));
        auto sequence = Sequence::create(delay, fade, nullptr);
        eyes->runAction(sequence);
    }
    
    // distance info label
    auto distLabelTitle = Label::createWithTTF("Distance:", "rsrc/Monster_AG.ttf", 65);
    _base->addChild(distLabelTitle);
    distLabelTitle->setAnchorPoint({0, 0.5});
    distLabelTitle->setPosition(baseSize.x * 0.3, baseSize.y * 0.7);
    distLabelTitle->setColor(Color3B(234, 222, 174));
    
    std::string dist = std::to_string(distance);
    auto distLabel = Label::createWithTTF(dist, "rsrc/Monster_AG.ttf", 65);
    _base->addChild(distLabel);
    distLabel->setAnchorPoint({0, 0.5});
    auto distPos = distLabelTitle->getPosition();
    distPos.x += distLabelTitle->getContentSize().width + baseSize.x * 0.02;
    distLabel->setPosition(distPos);
    distLabel->setColor(Color3B(234, 222, 174));
    
    // coins info label
    auto coinSign = Sprite::create("rsrc/deathmenu_coin_sign.png");
    _base->addChild(coinSign);
    coinSign->setAnchorPoint({0, 1});
    coinSign->setPosition(distLabelTitle->getPosition().x, distLabelTitle->getPosition().y - distLabelTitle->getContentSize().height);
    
    std::string co = std::to_string(coins);
    auto coinsLabel = Label::createWithTTF(co, "rsrc/Monster_AG.ttf", 120);
    _base->addChild(coinsLabel);
    coinsLabel->setAnchorPoint({0, 0.5});
    auto coinsPos = coinSign->getPosition();
    coinsPos.x += coinSign->getContentSize().width + baseSize.x * 0.02;
    coinsPos.y -= coinSign->getContentSize().height / 2;
    coinsLabel->setPosition(coinsPos);
    coinsLabel->setColor(Color3B(234, 222, 174));
    */
    return true;
}

void DeathMenu::onRestartClicked(gui2::Button *sender)
{
    close([=](){_hud->onRestartClicked();});
}

void DeathMenu::onMainMenuClicked(gui2::Button *sender)
{
    close([=](){_hud->onMainMenuClicked();});
}

void DeathMenu::close(const std::function<void ()> &hudCallback)
{
 
    Vec2 winSize = Convert::toPixels(Environment::getScreenSize());

    {
        auto move = EaseCubicActionIn::create(MoveTo::create(MenuMoveTime, {winSize.x * 0.5f, NodeUtils::getScaledSize(_deer).y * -0.5f}));
        auto delay = DelayTime::create(MenuCloseDelay);
        auto sequence = Sequence::create(delay, move, nullptr);
        _deer->runAction(sequence);
    }
    
    {
        auto delay = DelayTime::create(MenuMoveTime * 1.5);
        auto callback = CallFunc::create(hudCallback);
        auto sequence = Sequence::create(delay, callback, nullptr);
        runAction(sequence);
    }
}

