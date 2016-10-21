#include "MainMenuScene.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/TimeProvider.h"
#include "Utils/Environment.h"
#include "ForceField/ForceFieldFactory.h"
#include "ForceField/ForceFieldDebugDraw.h"
#include "Particles/ParticlesSystem.h"
#include "Particles/ParticlesGenerator.h"
#include "Particles/Particle.h"
#include "Particles/ParticlesMover.h"
#include "Particles/ParticlesReplacer.h"
#include "GUI/BoxLayout.h"
#include "GUI/Orientation.h"
#include "GUI/Alignment.h"
#include "GUI/View.h"
#include "GUI/ViewPort.h"
#include "GUI/Button.h"
#include "SceneManager.h"

USING_NS_CC;

MainMenuScene::MainMenuScene()
{}

MainMenuScene::~MainMenuScene()
{}

bool MainMenuScene::init()
{
	if (!GenericScene::init())
		return false;

	auto background = createBackground("resources/main_menu_background.png");
	addChild(background);

    auto timeProvider = TimeProvider::create();
    this->addUpdatable(timeProvider);
    
    auto particlesSystem = ParticlesFactory::createMainMenuParticlesSystem(timeProvider);
    this->addChild(particlesSystem.particlesNode);
    this->addUpdatable(particlesSystem.particlesSystem);
    
	auto decor = Sprite::create("resources/main_menu_grass.png");
	decor->setAnchorPoint(Vec2(0, 0));
	decor->setPosition(Vec2(0, 0));
    float decorScale = Convert::toPixels(Environment::getScreenSize().x) / decor->getContentSize().width;
	decor->setScale(decorScale);
	addChild(decor);

	//_forceDebugDraw = ForceFieldDebugDraw::create(forceField, fieldSize, 0.5, 15);
	//addChild(_forceDebugDraw);

    ////// trying to add several buttons
    
    _viewPort = gui::ViewPort::create(this);
    _viewPort->setSize(Director::getInstance()->getWinSize());
    
    auto baseView = gui::View::create();
    auto layout = gui::BoxLayout::create(gui::Orientation::Vertical, gui::Alignment::Center);
    baseView->setLayout(layout);
    
    auto restartButton = gui::Button::create("resources/restart_button_normal.png", "resources/restart_button_pressed.png");
    auto startGameCallback = [=](gui::Button* button)
    {
        SceneManager::getInstance()->showGameScene();
    };
    restartButton->setCallback(startGameCallback);
    
    auto settingsButton = gui::Button::create("resources/settings_button_normal.png", "resources/settings_button_pressed.png");
    
    baseView->addView(restartButton);
    baseView->setPosition(Vec2(_viewPort->getSize().x / 2, _viewPort->getSize().y / 2));
    _viewPort->addView(baseView);
    
    layout->doLayout(baseView, false);
    
    ////// end
    
	scheduleUpdate();
	return true;
}

Sprite* MainMenuScene::createBackground(const std::string & backgroundName)
{
	auto background = Sprite::create(backgroundName);
	Vec2 backgroundScale;
    backgroundScale.x = Convert::toPixels(Environment::getScreenSize().x) / background->getContentSize().width;
    backgroundScale.y = Convert::toPixels(Environment::getScreenSize().y) / background->getContentSize().height;
	background->setScale(backgroundScale.x, backgroundScale.y);
	background->setAnchorPoint(Vec2(0, 0));

	return background;
}
