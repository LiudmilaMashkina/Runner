#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>

#pragma warning(pop)

#include "IGameObject.h"
#include "Utils/MacroCreate.h"

namespace cocos2d { class Node; }
class GameWorld;

class BridgeColumn : public IGameObject
{
public:
    CREATE_FUNC_3(BridgeColumn, b2Body*, body, cocos2d::Node*, node, GameWorld*, world);
    
    virtual ~BridgeColumn();
    
    virtual void update(float delta) override;
    virtual b2Body* getBody() override { return _body; }
    virtual b2Vec2 getPosition() override;
    virtual GameObjectType getType() const override { return GameObjectType::BridgeColumn; }
    
    virtual void drop() override;
    virtual bool isDroppable() override { return true; }
    
    void setLeftMark(b2Vec2 leftMark);
    void setRightMark(b2Vec2 rightMark);
    b2Vec2 getLeftMark();
    b2Vec2 getRightMark();
    
private:
    BridgeColumn(b2Body* body, cocos2d::Node* node, GameWorld* world);

    b2Body* _body = nullptr;
    cocos2d::Node* _node = nullptr;
    GameWorld* _world = nullptr;
    b2Vec2 _leftMark = {0, 0};
    b2Vec2 _rightMark = {0, 0};
};

 
