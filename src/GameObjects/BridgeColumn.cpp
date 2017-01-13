
#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)

#include "BridgeColumn.h"
#include "GameWorld.h"
#include "Utils/Convert.h"

USING_NS_CC;

BridgeColumn::BridgeColumn(b2Body* body,
                           Node* node,
                           GameWorld* world) : SimpleGameObject::SimpleGameObject(body, node, world)
{
    update(0);
}

BridgeColumn::~BridgeColumn()
{}

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
