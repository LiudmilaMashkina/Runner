#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#pragma warning(push, 0)
#include <2d/CCSprite.h>
#pragma warning(pop)

#include "GameWorld.h"
#include "IGameObject.h"


class GameObjectFactory 
{
public:
	GameObjectFactory(GameWorld* world);
	std::shared_ptr<IGameObject> createSimpleObject();

private:
	b2Body * createBody(cocos2d::V3F_C4B_T2F * vertices, unsigned short * indices, int indicesSize);
	cocos2d::Sprite* createSprite(const std::string & textureName, cocos2d::V3F_C4B_T2F * verts, unsigned short * indices, int indexSize, int vertSize);

	GameWorld* _world = nullptr;

};
#endif // __GameObjectFactory__
 