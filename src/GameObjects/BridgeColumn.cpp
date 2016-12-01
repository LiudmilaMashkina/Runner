
#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "BridgeColumn.h"
#include "GameWorld.h"
#include "Utils/Convert.h"

USING_NS_CC;

BridgeColumn::BridgeColumn(b2Body* body,
                           Node* node,
                           GameWorld* world) :
_body(body),
_node(node),
_world(world)
{
    update(0);
}

BridgeColumn::~BridgeColumn()
{
    _node->removeFromParentAndCleanup(true);
    _world->getPhysics()->DestroyBody(_body);
}

void BridgeColumn::update(float delta)
{
    b2Vec2 bodyPos = _body->GetPosition();
    float bodyAngle = _body->GetAngle();
    
    _node->setPosition(Convert::toPixels(bodyPos));
    _node->setRotation(Convert::toDegrees(-bodyAngle));
}

b2Vec2 BridgeColumn::getPosition()
{
    return _body->GetPosition();
}

void BridgeColumn::drop()
{
    _body->SetType(b2BodyType::b2_dynamicBody);
    _body->SetLinearDamping(0.1f);
    _body->SetAngularDamping(0.1f);
    
    std::vector<b2Joint*> jointsToDelete;
    for (auto edge = _body->GetJointList(); edge != nullptr; edge = edge->next)
    {
        b2Joint *joint = edge->joint;
        jointsToDelete.push_back(joint);
    }
    
    for (int i = 0; i < jointsToDelete.size(); ++i)
    {
        _world->getPhysics()->DestroyJoint(jointsToDelete[i]);
    }
    
}

void BridgeColumn::setLeftMark(b2Vec2 leftMark)
{
    _leftMark = leftMark;
}

void BridgeColumn::setRightMark(b2Vec2 rightMark)
{
    _rightMark = rightMark;
}

b2Vec2 BridgeColumn::getLeftMark()
{
    return _leftMark;
}

b2Vec2 BridgeColumn::getRightMark()
{
    return _rightMark;
}
