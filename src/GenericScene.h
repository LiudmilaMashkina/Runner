#pragma once
#pragma warning(push, 0)
#include <2d/CCScene.h>
#pragma warning(pop)
#include <vector>
#include <memory>
#include "Utils/MacroCreate.h"

class IUpdatable;

class GenericScene : public cocos2d::Scene
{
public:
    virtual ~GenericScene();
    
    CC_CREATE_FUNC(GenericScene, init);
    
    virtual bool init() override;
    void update(float delta) override;
    
    void addUpdatable(const std::shared_ptr<IUpdatable> &updatable);
    
protected:
    GenericScene();
    
private:
    std::vector<std::shared_ptr<IUpdatable>> _updatables;
};
