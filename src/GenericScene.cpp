#include <cassert>
#include "GenericScene.h"
#include "IUpdatable.h"

USING_NS_CC;

GenericScene::~GenericScene()
{
    
}

GenericScene::GenericScene()
{
    
}

bool GenericScene::init()
{
    if (!Scene::init())
        return false;
 
    scheduleUpdate();
    return true;
}

void GenericScene::update(float delta)
{
    if (_isPaused)
        return;
    
    for (auto& updatable : _updatables)
        updatable->update(delta);
    
}

void GenericScene::addUpdatable(const std::shared_ptr<IUpdatable> &updatable)
{
    assert(updatable);
    assert(std::find(_updatables.begin(), _updatables.end(), updatable) == _updatables.end());
    _updatables.push_back(updatable);
}

void GenericScene::setPaused(bool isPaused)
{
    _isPaused = isPaused;
}
