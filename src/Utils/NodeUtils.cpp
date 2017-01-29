#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)
#include "NodeUtils.h"

USING_NS_CC;

void NodeUtils::scaleTo(cocos2d::Node *node, const cocos2d::Vec2 &size)
{
    Vec2 scale;
    scale.x = size.x / node->getContentSize().width;
    scale.y = size.y / node->getContentSize().height;
    node->setScale(scale.x, scale.y);
}

void NodeUtils::attach(cocos2d::Node *node,
                       cocos2d::Node *parent,
                       const cocos2d::Vec2 posPercent,
                       int zOrder)
{
    assert(node);
    assert(parent);
    
    parent->addChild(node, zOrder);
    node->setPosition(posPercent.x * parent->getContentSize().width,
                      posPercent.y * parent->getContentSize().height);
}

cocos2d::Vec2 NodeUtils::getScaledSize(cocos2d::Node *node)
{
    return Vec2(node->getContentSize().width * node->getScaleX(),
                node->getContentSize().height * node->getScaleY());
}
