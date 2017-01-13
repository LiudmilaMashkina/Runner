#pragma once

#pragma warning(push, 0)
#include <Box2D/Dynamics/b2Body.h>

#pragma warning(pop)

#include "SimpleGameObject.h"
#include "Utils/MacroCreate.h"

namespace cocos2d { class Node; }
class GameWorld;

class BridgeColumn : public SimpleGameObject
{
public:
    CREATE_FUNC_3(BridgeColumn, b2Body*, body, cocos2d::Node*, node, GameWorld*, world);
    
    virtual ~BridgeColumn();
    
    virtual GameObjectType getType() const override { return GameObjectType::BridgeColumn; }
    
    virtual void drop() override;
    
    void setLeftMark(b2Vec2 leftMark);
    void setRightMark(b2Vec2 rightMark);
    b2Vec2 getLeftMark();
    b2Vec2 getRightMark();
    
private:
    BridgeColumn(b2Body* body, cocos2d::Node* node, GameWorld* world);

    b2Vec2 _leftMark = {0, 0};
    b2Vec2 _rightMark = {0, 0};
};

 
