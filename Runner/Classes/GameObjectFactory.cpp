#pragma warning(push, 0)

#pragma warning(pop)

#include "GameObjectFactory.h"
#include "IGameObject.h"
#include "SimpleGameObject.h"

USING_NS_CC;

GameObjectFactory::GameObjectFactory(GameWorld* world) :
_world(world)
{}

std::shared_ptr<IGameObject> GameObjectFactory::createBox(const b2Vec2& pos)
{
	b2PolygonShape physShape;
	physShape.SetAsBox(1, 1);

	b2Body* body = createBody(b2BodyType::b2_staticBody, physShape);
	
	body->SetTransform(pos, body->GetAngle());

	Sprite* sprite = createSprite("stone_basic_blue_1.png");
	
	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);

	return obj;
}

std::shared_ptr<IGameObject> GameObjectFactory::createCircle(const b2Vec2& pos)
{
	b2CircleShape physShape;
	physShape.m_p.Set(0, 0);
	physShape.m_radius = 1;

	b2Body* body = createBody(b2BodyType::b2_dynamicBody, physShape);
	
	body->SetTransform(pos, body->GetAngle());

	Sprite* sprite = createSprite("stone_basic_blue_3.png");

	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);

	return obj;
}

b2Body* GameObjectFactory::createBody(const b2BodyType& t, const b2Shape& sh)
{
	b2BodyDef bodyDef;
	bodyDef.type = t;
	b2Body* body = _world->getPhysics()->CreateBody(&bodyDef);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = &sh;
	bodyFixtureDef.density = 1;
	body->CreateFixture(&bodyFixtureDef);

	return body;
}

Sprite* GameObjectFactory::createSprite(const std::string& textureName)
{
	auto sprite = Sprite::create(textureName);
	_world->getGraphics()->addChild(sprite);

	return sprite;
}


