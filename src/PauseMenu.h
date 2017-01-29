 #pragma once

#include "GUI/ViewPort.h"
#include "SceneManager.h"
#include "Utils/MacroCreate.h"
#include "Utils/StrongPtr.h"

namespace gui
{
    class ProgressBar;
    class Button;
    class Label;
}

namespace gui2
{
    class Button;
    class CheckBox;
}

class HeadUpDisplay;

class PauseMenu : public cocos2d::Node
{
public:
    PauseMenu();
	virtual ~PauseMenu();

    CC_CREATE_FUNC_1(PauseMenu, initWithHud,
                     HeadUpDisplay*, hud);
    
    void onContinueClicked(gui2::Button* sender);
    void onRestartClicked(gui2::Button* sender);
    void onMainMenuClicked(gui2::Button* sender);
    
private:
    bool initWithHud(HeadUpDisplay* hud);
    void close(const std::function<void()> &hudCallback);
    
    static void openWing(gui2::Button* button, float targetRotation);
    static void closeWing(gui2::Button *button);
    static void turnOnCheckBox(gui2::CheckBox* checkBox);
    static void turnOffCheckBox(gui2::CheckBox* checkBox);
    
    HeadUpDisplay* _hud = nullptr;
    
    cocos2d::Sprite* _background = nullptr;
    cocos2d::Sprite* _totem = nullptr;
    
    gui2::Button* _continueButton = nullptr;
    gui2::Button* _restartButton = nullptr;
    gui2::Button* _mainMenuButton = nullptr;
    
    gui2::CheckBox* _soundsCheckBox = nullptr;
    gui2::CheckBox* _musicCheckBox = nullptr;
};
