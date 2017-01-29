#pragma once

#include "Utils/Forwards.h"
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2Fixture.h>
#include "GameObjects/CollisionCategory.h"

FORWARD_DECLARE_SHARED(AnimationEngine)

namespace cocos2d
{
    class Node;
}

/* HeroData is a common part for both Hero and hero states
 */
struct HeroData
{
    HeroData()
    {
        collisionFilter.categoryBits = HeroCategory;
        collisionFilter.maskBits = DefaultCategory;
    }
    
    b2Vec2 acceleration = {0, 0};
    b2Vec2 velocity = {0, 0};
    cocos2d::Node* node = nullptr;
    b2Body* body = nullptr;
    AnimationEnginePtr animationEngine;
    bool canAttack = true;
    b2Filter collisionFilter;
};
