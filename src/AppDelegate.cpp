#pragma warning(push, 0)
#include <platform/CCGLView.h>
#include <base/CCDirector.h>
#ifdef MAC
#include <platform/desktop/CCGLViewImpl-desktop.h>
#endif
#pragma warning(pop)
#include "AppDelegate.h"
#include "DataBase.h"
#include "TestScene.h"
#include "GenericScene.h"
#include "SceneManager.h"
#include "AudioEngine.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	srand(static_cast<unsigned int>(time(0)));

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("RunnerCocos", cocos2d::Rect(0, 0, 1136, 640));
#else
        glview = GLViewImpl::create("RunnerCocos");
#endif
        director->setOpenGLView(glview);
    }
    
    auto foo = director->getWinSize();

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    foo = director->getWinSize();
    
#ifdef WIN32
	director->getOpenGLView()->setFrameSize(1136, 640);
	director->getOpenGLView()->setDesignResetOpenGLViewsolutionSize(1136, 640, ResolutionPolicy::EXACT_FIT);
#endif

    register_all_packages();
    
    
    SceneManager* manager = SceneManager::getInstance();
    manager->showMainMenu();
    
    
    
    //auto condition = DataBase::getInstace()->getBoolForKey("music");
    
    AudioEngine::getInstance()->preloadMusic();
    
    if (DataBase::getInstace()->getBoolForKey("music"))
        AudioEngine::getInstance()->playMusic();
    else
        DataBase::getInstace()->setBoolForKey("music", false);
    
    
    
    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
