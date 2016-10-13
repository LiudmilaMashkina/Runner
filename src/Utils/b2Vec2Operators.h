#pragma once

#include "Box2D/Common/b2Math.h"

inline b2Vec2 operator*(const b2Vec2 &v, float32 n)
{
    return b2Vec2(v.x * n, v.y * n);
}

inline b2Vec2 operator/(const b2Vec2 &v, float32 n)
{
    return b2Vec2(v.x / n, v.y / n);
}
