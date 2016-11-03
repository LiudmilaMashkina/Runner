#pragma once

#include "Utils/Forwards.h"
#include <Box2D/Dynamics/b2Body.h>

FORWARD_DECLARE_SHARED(AnimationEngine)

namespace cocos2d
{
    class Node;
}

/* HeroData is a common part for both Hero and hero states
 */
struct HeroData
{
    b2Vec2 acceleration;
    b2Vec2 velocity;
    cocos2d::Node* node = nullptr;
    b2Body* body = nullptr;
    AnimationEnginePtr animationEngine;
    bool canAttack = true;
};
