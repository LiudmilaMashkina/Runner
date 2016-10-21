#pragma once

#include <memory>
#include <Box2D/Box2D.h>

class b2Utils
{
public:
    static float raycast(std::shared_ptr<b2World> b2world, const b2Vec2 &source, const b2Vec2 &direction);
};
