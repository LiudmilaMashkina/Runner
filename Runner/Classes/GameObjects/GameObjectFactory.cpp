#pragma warning(push, 0)

#pragma warning(pop)

#include "GameObjectFactory.h"
#include "IGameObject.h"
#include "SimpleGameObject.h"
#include "Utils/Convert.h"

USING_NS_CC;

GameObjectFactory::GameObjectFactory(GameWorld* world) :
	_world(world)
{}

std::shared_ptr<IGameObject> GameObjectFactory::createBox(const b2Vec2& pos, float angle, const b2Vec2& size, b2BodyType type, const std::string fileName)
{
	b2PolygonShape physShape;
	physShape.SetAsBox(size.x / 2, size.y / 2, b2Vec2(size.x / 2, size.y / 2), 0);
	
	b2Body* body = createBody(type, &physShape, pos, angle);

	Sprite* sprite = createSprite(fileName, size);
	sprite->setAnchorPoint(Vec2(0, 0));

	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);

	return obj;
}

std::shared_ptr<IGameObject> GameObjectFactory::createCircle(const b2Vec2& pos, float angle, float radius, b2BodyType type, const std::string fileName)
{
	b2CircleShape physShape;
	physShape.m_p.Set(0, 0);
	physShape.m_radius = radius;

	b2Body* body = createBody(b2BodyType::b2_dynamicBody, &physShape, pos, angle);

	Sprite* sprite = createSprite(fileName, b2Vec2(radius * 2, radius * 2));

	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);

	return obj;
}

b2Body* GameObjectFactory::createBody(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle)
{
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position = pos;
	bodyDef.angle = angle;
	b2Body* body = _world->getPhysics()->CreateBody(&bodyDef);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = shape;
	bodyFixtureDef.density = 1;
	body->CreateFixture(&bodyFixtureDef);

	return body;
}

Sprite* GameObjectFactory::createSprite(const std::string& textureName, const b2Vec2& bodySize)
{
	auto sprite = Sprite::create(textureName);
	_world->getGraphics()->addChild(sprite);

	scale(bodySize, sprite);

	return sprite;
}

void GameObjectFactory::scale(const b2Vec2& size, cocos2d::Sprite * sprite)
{
	Size spriteSize = sprite->getContentSize();

	Vec2 scale;
	scale.x = Convert::toPixels(size.x) / spriteSize.width;
	scale.y = Convert::toPixels(size.y) / spriteSize.height;

	sprite->setScale(scale.x, scale.y);
}


