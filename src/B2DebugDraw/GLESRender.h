/*******************************************************************************************************/
/*
 *
 * @File:           Render.h
 * @Group:          Libraries
 * @Version:        Revision: 1.2.9   (Cocos2d-x V3.X)
 * @Last changed:   Date: 2014/08/06 08:03:06
 * @Created:        Date: 2014/08/05 05:03:06
 * @Purpose:        Define all class, function and variables for Render.cpp object file.
 * @Author:         Harion
 * @Copyright:      (C)2012-2015 CreativeGame - G2TVN.,Corp
 * @Product:        :HerosWorld:
 *
 */
/*******************************************************************************************************/

#pragma once

#include <Box2D/Box2D.h>

namespace cocos2d
{
    class GLProgram;
}

struct b2AABB;

class GLESDebugDraw : public b2Draw {
     float32 mRatio;
    cocos2d::GLProgram * mShaderProgram;
     int       mColorLocation;

     void initShader( void );
public:
     GLESDebugDraw();
     
     GLESDebugDraw( float32 ratio );

     virtual void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);
     virtual void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);
     virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
     virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
     virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
     virtual void DrawTransform(const b2Transform& xf);
     virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
     virtual void DrawString(int x, int y, const char* string, ...);
     virtual void DrawAABB(b2AABB* aabb, const b2Color& color);
};
