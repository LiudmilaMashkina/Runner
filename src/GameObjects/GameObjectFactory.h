#pragma once

#pragma warning(push, 0)
#include <2d/CCSprite.h>
#pragma warning(pop)

#include "GameWorld.h"
#include "IGameObject.h"

class SimpleGameObject;
class Bomb;

class GameObjectFactory 
{
public:
	GameObjectFactory(GameWorld* world);
	std::shared_ptr<SimpleGameObject> createBox(const b2Vec2& pos, float angle, const b2Vec2& size, b2BodyType type, const std::string& fileName);
	std::shared_ptr<IGameObject> createStaticStone(const b2Vec2& topLeftCornerPos, float width, const std::string& fileName);
	std::shared_ptr<IGameObject> createCircle(const b2Vec2& pos, float angle, float radius, b2BodyType type, const std::string& fileName);
    std::shared_ptr<Bomb> createBomb(const b2Vec2& pos, float angle, const b2Vec2& size);

private:
	b2Body* createBody(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle);
    b2Body* createSensor(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle);
	cocos2d::Sprite* createSprite(const std::string& textureName, const b2Vec2& bodySize);
	cocos2d::Sprite* createSprite(const std::string& textureName);

	static void scale(const b2Vec2& size, cocos2d::Sprite* sprite);

	GameWorld* _world = nullptr;
}; 
