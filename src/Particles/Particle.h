#pragma once

#include <2d/CCNode.h>
#include <Box2D/Common/b2Math.h>

struct Particle
{
    cocos2d::Node* sprite = nullptr;
    b2Vec2 velocity;
    float mass = 0;
    float ttl = 0;
    float startTtl = 0;
};
