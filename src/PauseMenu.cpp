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
#include "PauseMenu.h"


USING_NS_CC;

namespace
{
    const float TotemMoveTime = 0.5;
    const float WingMoveTime = 0.5;
    const float WingMoveDelay = TotemMoveTime * 0.8;
    const float CheckBoxFadeDuration = 0.5;
    const float CheckBoxFadeDelay = TotemMoveTime * 0.8;
    const float WingInitRotation = -100;
    const float TotemMoveBackDelay = CheckBoxFadeDuration * 0.8;
    const float TotemEaseRate = 5;
    const float BackgroundFadeTime = 0.5;
}

PauseMenu::PauseMenu()
{
    
}

PauseMenu::~PauseMenu()
{
    
}

bool PauseMenu::initWithHud(HeadUpDisplay* hud)
{
    if (!Node::init())
        return false;
        
    _hud = hud;
    
    Vec2 winSize = Convert::toPixels(Environment::getScreenSize());
    
    {
        _background = Sprite::create("rsrc/pause_menu_background_256x256.png");
        NodeUtils::scaleTo(_background, {winSize.x * 0.6f, winSize.y});
        _background->setAnchorPoint({1, 1});
        _background->setPosition(winSize);
        addChild(_background);
        
        _background->setOpacity(0);
        auto fade = EaseCubicActionIn::create(FadeTo::create(BackgroundFadeTime, 255));
        _background->runAction(fade);
    }
    
    {
        _totem = Sprite::create("rsrc/pause_menu_totem.png");
        _totem->setAnchorPoint({1, 0.5});
        _totem->setPosition(winSize.x + NodeUtils::getScaledSize(_totem).x, winSize.y / 2);
        float scale = winSize.y * 0.8 / _totem->getContentSize().height;
        _totem->setScale(scale);
        addChild(_totem);
        
        auto move = EaseOut::create(MoveTo::create(TotemMoveTime,
                                                        {winSize.x, winSize.y / 2}), TotemEaseRate);
        _totem->runAction(move);
    }
    
    {
        // continue button
        auto button = gui2::Button::create("rsrc/pause_menu_continue.png",
                                           "rsrc/pause_menu_continue_pressed.png");
        button->setCallback(std::bind(&PauseMenu::onContinueClicked, this, std::placeholders::_1));
        
        button->setAnchorPoint({1, 1});
        NodeUtils::attach(button, _totem, {0.4, 0.8}, -1);
        button->setRotation(WingInitRotation);
        openWing(button, 0);
        _continueButton = button;
    }

    {
        // restart button
        auto button = gui2::Button::create("rsrc/pause_menu_restart.png",
                                           "rsrc/pause_menu_restart_pressed.png");
        button->setCallback(std::bind(&PauseMenu::onRestartClicked, this, std::placeholders::_1));

        button->setAnchorPoint({1, 1});
        NodeUtils::attach(button, _totem, {0.4, 0.7}, -1);
        button->setRotation(WingInitRotation);
        openWing(button, -20);
        _restartButton = button;
    }
    
    {
        // main menu button
        auto button = gui2::Button::create("rsrc/pause_menu_mainmenu.png",
                                           "rsrc/pause_menu_mainmenu_pressed.png");
        button->setCallback(std::bind(&PauseMenu::onMainMenuClicked, this, std::placeholders::_1));

        button->setAnchorPoint({1, 1});
        NodeUtils::attach(button, _totem, {0.4, 0.6}, -1);
        button->setRotation(WingInitRotation);
        openWing(button, -45);
        _mainMenuButton = button;
    }
    
    {
        // sound check box
        auto checkBox = gui2::CheckBox::create("rsrc/pause_menu_sounds_on.png",
                                               "rsrc/pause_menu_sounds_off.png");
        checkBox->setAnchorPoint({1, 0});
        NodeUtils::attach(checkBox, _totem, {-1.4, 0.8});
        turnOnCheckBox(checkBox);
        _soundsCheckBox = checkBox;
    }
    
    {
        // music check box
        auto checkBox = gui2::CheckBox::create("rsrc/pause_menu_music_on.png",
                                               "rsrc/pause_menu_music_off.png");
        checkBox->setAnchorPoint({0, 0});
        NodeUtils::attach(checkBox, _totem, {-1.2, 0.8});
        turnOnCheckBox(checkBox);
        _musicCheckBox = checkBox;
    }
    
    return true;
}

void PauseMenu::onContinueClicked(gui2::Button *sender)
{
    close([=](){_hud->onContinueClicked();});
}

void PauseMenu::onRestartClicked(gui2::Button *sender)
{
    close([=](){_hud->onRestartClicked();});
}

void PauseMenu::onMainMenuClicked(gui2::Button *sender)
{
    close([=](){_hud->onMainMenuClicked();});
}

void PauseMenu::close(const std::function<void ()> &hudCallback)
{
    Vec2 winSize = Convert::toPixels(Environment::getScreenSize());

    turnOffCheckBox(_soundsCheckBox);
    turnOffCheckBox(_musicCheckBox);
    closeWing(_continueButton);
    closeWing(_restartButton);
    closeWing(_mainMenuButton);
    
    {
        auto move = EaseIn::create(MoveTo::create(TotemMoveTime, {winSize.x + NodeUtils::getScaledSize(_totem).x, winSize.y / 2}), TotemEaseRate);
        auto delay = DelayTime::create(TotemMoveBackDelay);
        auto sequence = Sequence::create(delay, move, nullptr);
        _totem->runAction(sequence);
    }
    
    {
        auto fade = EaseCubicActionOut::create(FadeTo::create(BackgroundFadeTime, 0));
        _background->runAction(fade);
    }
    
    {
        auto delay = DelayTime::create(TotemMoveBackDelay + TotemMoveTime);
        auto callback = CallFunc::create(hudCallback);
        auto sequence = Sequence::create(delay, callback, nullptr);
        runAction(sequence);
    }
}

void PauseMenu::openWing(gui2::Button* button, float targetRotation)
{
    button->setEnabled(false);
    auto delay = DelayTime::create(WingMoveDelay);
    auto rotate = EaseBackOut::create(RotateTo::create(WingMoveTime, targetRotation));
    auto enable = CallFunc::create([=](){button->setEnabled(true);});
    auto sequence = Sequence::create(rotate, delay, enable, nullptr);
    button->runAction(sequence);
}

void PauseMenu::closeWing(gui2::Button *button)
{
    button->setEnabled(false);
    auto rotate = EaseBackIn::create(RotateTo::create(WingMoveTime, WingInitRotation));
    button->runAction(rotate);
}

void PauseMenu::turnOnCheckBox(gui2::CheckBox *checkBox)
{
    checkBox->setEnabled(false);
    checkBox->setOpacity(0);
    auto delay = DelayTime::create(CheckBoxFadeDelay);
    auto fade = EaseCubicActionIn::create(FadeTo::create(CheckBoxFadeDuration, 255));
    auto enable = CallFunc::create([=](){checkBox->setEnabled(true);});
    auto sequence = Sequence::create(delay, fade, enable, nullptr);
    checkBox->runAction(sequence);
}

void PauseMenu::turnOffCheckBox(gui2::CheckBox *checkBox)
{
    checkBox->setEnabled(false);
    auto fade = EaseCubicActionOut::create(FadeTo::create(CheckBoxFadeDuration, 0));
    checkBox->runAction(fade);
}



