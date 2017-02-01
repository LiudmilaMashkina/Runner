#include "MainMenuScene.h"
#include "AnimationEngine/Animation.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "Utils/TimeProvider.h"
#include "Utils/Environment.h"
#include "Utils/NodeUtils.h"
#include "Utils/StrongPtr.h"
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
#include "GUI/CheckBox.h"
#include "GUI/Placer.h"
#include "GUI2/Button.h"
#include "GUI2/CheckBox.h"
#include "SceneManager.h"

USING_NS_CC;

namespace
{
    /*
    struct lightsRange
    {
        Vec2 width = {0.0, 0.0};
        Vec2 height = {0.0, 0.0};
        
        lightsRange set(Vec2 widthRange, Vec2 heightRange)
        {
            lightsRange res;
            res.width = widthRange;
            res.height = heightRange;
            return res;
        }
    };
*/
    const float EyesFadeTime = 0.4;
    const float EyesFadeDelay = 0.7;
    const float CheckBoxFadeDuration = 0.5;
    const float CheckBoxFadeDelay = EyesFadeDelay * 0.5;
    //const lightsRange lightsR.set({3, 5}, {3, 6});
}


MainMenuScene::MainMenuScene()
{}

MainMenuScene::~MainMenuScene()
{}

bool MainMenuScene::init()
{
	if (!GenericScene::init())
		return false;

	auto background = createBackground("resources/mainmenu_background_512x512.png");
	addChild(background);
    
    auto winSize = Convert::toPixels(Environment::getScreenSize());
    
    auto grassTexture = TextureCache::getInstance()->addImage("resources/mainmenu_grass.png");
    Size grassSize = grassTexture->getContentSize();
    float scale = winSize.y * 0.26 / grassSize.height;
    
    createGrass({winSize.x * -0.05f, 0}, winSize.x, scale);
    
    auto timeProvider = TimeProvider::create();
    this->addUpdatable(timeProvider);
    
    auto particlesSystem = ParticlesFactory::createMainMenuParticlesSystem(timeProvider);
    this->addChild(particlesSystem.particlesNode);
    this->addUpdatable(particlesSystem.particlesSystem);
    
    createNorthLights(winSize);
    
    auto totem = Sprite::create("resources/mainmenu_totem.png");
    addChild(totem);
    totem->setAnchorPoint({0.5, 0.65});
    totem->setScale(scale);
    totem->setPosition(winSize /2);
    
    auto button = gui2::Button::create("resources/mainmenu_start.png", "resources/mainmenu_start_pressed.png");
    button->setAnchorPoint({0.5, 1});
    NodeUtils::attach(button, totem, {0.49, 0.6});
    
    auto startGameCallback = [=](gui2::Button* startButton)
    {
        SceneManager::getInstance()->showGameScene();
    };
    button->setCallback(startGameCallback);
    
    // eyes
    auto eyes = Sprite::create("resources/mainmenu_bull_eyes.png");
    NodeUtils::attach(eyes, totem, {0.5, 0.695}, 1);
    
    eyes->setOpacity(0);
    auto delay = DelayTime::create(EyesFadeDelay);
    auto fade = EaseExponentialIn::create(FadeTo::create(EyesFadeTime, 255));
    auto sequence = Sequence::create(delay, fade, nullptr);
    eyes->runAction(sequence);

    {
        // sound check box
        auto checkBox = gui2::CheckBox::create("resources/mainmenu_sounds_on.png",
                                               "resources/mainmenu_sounds_off.png");
        checkBox->setAnchorPoint({0, 0});
        NodeUtils::attach(checkBox, totem, {0.02, 0.52});
        turnOnCheckBox(checkBox);
    }
    
    {
        // music check box
        auto checkBox = gui2::CheckBox::create("resources/mainmenu_music_on.png",
                                               "resources/mainmenu_music_off.png");
        checkBox->setAnchorPoint({1, 0});
        NodeUtils::attach(checkBox, totem, {0.98, 0.52});
        turnOnCheckBox(checkBox);
    }
    
    // FIRE!
    auto fire = createFire(scale);
    NodeUtils::attach(fire, totem, {0.5, 0.9});
    
    auto fireParticleSystem = ParticlesFactory::createMainMenuFireParticleSystem(timeProvider, fire);
    this->addUpdatable(fireParticleSystem.particlesSystem);

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

void MainMenuScene::createGrass(Vec2 startPos, float untilX, float scale)
{
    while (startPos.x <= untilX)
    {
        auto grass = Sprite::create("resources/mainmenu_grass.png");
        addChild(grass);
        grass->setScale(scale);
        grass->setAnchorPoint({0, 0});
        grass->setPosition(startPos);
        startPos.x += NodeUtils::getScaledSize(grass).x * 0.7;
    }
}

void MainMenuScene::createNorthLights(const Vec2& winSize)
{
    float leftEdge = winSize.x * 0.3 * -1;
    std::vector<Color3B> colors;
    colors.push_back(Color3B(116, 255, 217));
    colors.push_back(Color3B(139, 232, 255));
    colors.push_back(Color3B(225, 161, 255));
    colors.push_back(Color3B(65, 253, 255));
    colors.push_back(Color3B::WHITE);
    
    while (leftEdge <= winSize.x)
    {
        auto light = Sprite::create("resources/mainmenu_background_light_1_128x256.png");
        addChild(light);
        light->setAnchorPoint({0, 0});
        
        float widthPercentage = Environment::generateFloatRand(0.3, 0.8);
        float heightPercentage = Environment::generateFloatRand(0.7, 2.0);
        
        NodeUtils::scaleTo(light, {winSize.x * widthPercentage, winSize.y * heightPercentage});
        light->setPosition(leftEdge, 0);
        leftEdge += NodeUtils::getScaledSize(light).x * 0.4;
        
        float startOpacity = Environment::generateIntRand(0, 190);
        light->setOpacity(startOpacity);
        int startColor = Environment::generateIntRand(0, colors.size() - 1);
        light->setColor(colors[startColor]);
        
        float appearTime = Environment::generateFloatRand(4.0, 6.0);
        auto appear = EaseExponentialIn::create(FadeTo::create(appearTime, 200));
        
        float delayTime = Environment::generateFloatRand(0.5, 1.0);
        auto delay = DelayTime::create(delayTime);
        
        float fadeTime = Environment::generateFloatRand(3.0, 8.0);
        auto fade = EaseExponentialIn::create(FadeTo::create(fadeTime, 80));
        
        float tintTime = Environment::generateFloatRand(3.0, 5.0);
        int color1 = Environment::generateIntRand(0, colors.size() - 1);
        auto tint1 = EaseExponentialIn::create(TintTo::create(tintTime, colors[color1]));
        
        int color2 = Environment::generateIntRand(0, colors.size() - 1);
        auto tint2 = EaseExponentialIn::create(TintTo::create(tintTime, colors[color2]));
        
        auto tintToWhite = EaseExponentialIn::create(TintTo::create(tintTime, Color3B::WHITE));
        
        auto sequence = Sequence::create(appear, delay, tint1, fade, delay, appear, tint1, delay,fade, tint2, appear, delay, tintToWhite, fade, nullptr);
        
        auto repeat = RepeatForever::create(sequence);
        light->runAction(repeat);
    }
    
}

void MainMenuScene::turnOnCheckBox(gui2::CheckBox *checkBox)
{
    checkBox->setEnabled(false);
    checkBox->setOpacity(0);
    auto delay = DelayTime::create(CheckBoxFadeDelay);
    auto fade = EaseCubicActionIn::create(FadeTo::create(CheckBoxFadeDuration, 255));
    auto enable = CallFunc::create([=](){checkBox->setEnabled(true);});
    auto sequence = Sequence::create(delay, fade, enable, nullptr);
    checkBox->runAction(sequence);
}

void MainMenuScene::turnOffCheckBox(gui2::CheckBox *checkBox)
{
    checkBox->setEnabled(false);
    auto fade = EaseCubicActionOut::create(FadeTo::create(CheckBoxFadeDuration, 0));
    checkBox->runAction(fade);
}

Sprite* MainMenuScene::createFire(float scale)
{
/*
    auto anim = Animation::create("filename_{0-6}.png", 10, true);
    addUpdatable(anim);
    return anim->getTarget();
*/
 
    Vector<SpriteFrame*> frames;
    for (int i = 0; i < 7; ++i)
    {
        std::string fString = "resources/mainmenu_fire_" + std::to_string(i) + ".png";
        auto texture = TextureCache::getInstance()->addImage(fString);
        Rect fRect;
        fRect.size = texture->getContentSize();
        fRect.origin = Vec2(0, 0);
        SpriteFrame* frame = SpriteFrame::create(fString, fRect);
        frames.pushBack(frame);
    }
    
    assert(!frames.empty());
    IAnimationPtr animation = std::shared_ptr<::Animation>(new ::Animation(frames, 15, true));
    
    StrongPtr<Sprite> sprite;
    sprite.reset(cocos2d::Sprite::createWithSpriteFrame(frames.at(0)));
    assert(sprite.get());
    animation->setTarget(sprite.get());
    this->addUpdatable(animation);
    
    return sprite.get();
}

