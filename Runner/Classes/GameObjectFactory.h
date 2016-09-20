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
	std::shared_ptr<IGameObject> createBox(const b2Vec2& pos);
	std::shared_ptr<IGameObject> createCircle(const b2Vec2& pos);

private:
	b2Body* createBody(const b2BodyType& t, const b2Shape& sh);
	cocos2d::Sprite* createSprite(const std::string& textureName);

	GameWorld* _world = nullptr;

};
#endif // __GameObjectFactory__
 