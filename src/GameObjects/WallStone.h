#pragma once

#pragma warning(push, 0)
#pragma warning(pop)

#include "IGameObject.h"
#include "Utils/MacroCreate.h"

class GameWorld;
class WallController;

class WallStone : public IGameObject
{
public:
    CREATE_FUNC_4(WallStone, b2Body*, body, cocos2d::Node*, node, GameWorld*, world, std::weak_ptr<WallController>, wController);
    
    virtual ~WallStone();
    
    virtual void update(float delta) override;
    virtual b2Body* getBody() override { return _body; }
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override { return GameObjectType::WallStone; }
    
    virtual void drop() override;
    virtual bool isDroppable() override { return true; }
    
    virtual void onContactBegin(std::shared_ptr<IGameObject> obj) override;
    
private:
    WallStone(b2Body* body, cocos2d::Node* node, GameWorld* world, std::weak_ptr<WallController> wController);
    
    b2Body* _body = nullptr;
    cocos2d::Node* _node = nullptr;
    GameWorld* _world = nullptr;
    std::weak_ptr<WallController> _wController;
    
};

 
