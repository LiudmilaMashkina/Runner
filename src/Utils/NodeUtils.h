#pragma once

#pragma warning(push, 0)
#include <math/Vec2.h>
#pragma warning(pop)

namespace cocos2d
{
    class Node;
}

class NodeUtils
{
public:
    static void scaleTo(cocos2d::Node *node, const cocos2d::Vec2 &size);
    static void attach(cocos2d::Node *node,
                       cocos2d::Node *parent,
                       const cocos2d::Vec2 posPercent,
                       int zOrder = 0);
    static cocos2d::Vec2 getScaledSize(cocos2d::Node *node);
};

