//
//  b2Vec2Operators.h
//  Wanderer
//
//  Created by Luda on 25/10/15.
//
//

#ifndef Wanderer_b2Vec2Operators_h
#define Wanderer_b2Vec2Operators_h

#include "Box2D/Common/b2Math.h"

inline b2Vec2 operator*(const b2Vec2 &v, float32 n)
{
    return b2Vec2(v.x * n, v.y * n);
}

inline b2Vec2 operator/(const b2Vec2 &v, float32 n)
{
    return b2Vec2(v.x / n, v.y / n);
}


#endif
