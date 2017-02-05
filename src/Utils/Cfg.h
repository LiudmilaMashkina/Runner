#pragma once

#pragma warning(push, 0)
#include <Box2D/Common/b2Math.h>
#include <math/Vec2.h>
#pragma warning(pop)

class Cfg
{
public:
    class Env
    {
    public:
        static const float GravityY;
    };
    
    class Hero
    {
    public:
        static const float VelocityX;
        static const float JumpVelocityY;
    };
};

