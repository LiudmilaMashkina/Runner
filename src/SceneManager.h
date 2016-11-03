#pragma once

#include "cocos2d.h" // ask Andrew


class SceneManager
{
public:
    static SceneManager* getInstance();
    
    void showMainMenu();
    void showGameScene();

private:
    SceneManager() {}
    
	void setScene(cocos2d::Scene* scene);

	cocos2d::Scene* _scene = nullptr;
    static SceneManager* _manager;
};
