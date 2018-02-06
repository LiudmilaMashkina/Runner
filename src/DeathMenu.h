 #pragma once

#include "GUI/ViewPort.h"
#include "SceneManager.h"
#include "Utils/MacroCreate.h"
#include "Utils/StrongPtr.h"

namespace gui2
{
    class Button;
}

class HeadUpDisplay;

class DeathMenu : public cocos2d::Node
{
public:
    DeathMenu();
	virtual ~DeathMenu();

    CC_CREATE_FUNC_3(DeathMenu, initWithHud,
                     HeadUpDisplay*, hud, int, distance, int, coins);
    
    void onRestartClicked(gui2::Button* sender);
    void onMainMenuClicked(gui2::Button* sender);
    
private:
    bool initWithHud(HeadUpDisplay* hud, int distance, int coins);
    void close(const std::function<void()> &hudCallback);
    
    HeadUpDisplay* _hud = nullptr;
    cocos2d::Sprite* _deer = nullptr;
};
