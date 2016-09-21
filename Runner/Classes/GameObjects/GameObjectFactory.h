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
	std::shared_ptr<IGameObject> createBox(const b2Vec2& pos, float angle, const b2Vec2& size, b2BodyType type, const std::string fileName);
	std::shared_ptr<IGameObject> createCircle(const b2Vec2& pos, float angle, float radius, b2BodyType type, const std::string fileName);

private:
	b2Body* createBody(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle);
	cocos2d::Sprite* createSprite(const std::string& textureName, const b2Vec2& bodySize);
	static void scale(const b2Vec2& size, cocos2d::Sprite* sprite);

	GameWorld* _world = nullptr;

};
#endif // __GameObjectFactory__
 