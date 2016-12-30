#pragma once

#pragma warning(push, 0)
#pragma warning(pop)

#include "SimpleGameObject.h"
#include "Utils/MacroCreate.h"

class GameWorld;
class WallController;

class WallStone : public SimpleGameObject
{
public:
    CREATE_FUNC_4(WallStone, b2Body*, body, cocos2d::Node*, node, GameWorld*, world, std::weak_ptr<WallController>, wController);
    
    virtual ~WallStone();
    
    virtual GameObjectType getType() const override { return GameObjectType::WallStone; }
    
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    
private:
    WallStone(b2Body* body, cocos2d::Node* node, GameWorld* world, std::weak_ptr<WallController> wController);
    
    std::weak_ptr<WallController> _wController;
};

 
