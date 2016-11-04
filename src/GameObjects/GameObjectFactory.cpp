#pragma warning(push, 0)
#include <2d/CCSpriteFrame.h>
#pragma warning(pop)

#include "GameObjectFactory.h"
#include "IGameObject.h"
#include "SimpleGameObject.h"
#include "Bomb.h"
#include "AnimationObject.h"
#include "Utils/Convert.h"

USING_NS_CC;

GameObjectFactory::GameObjectFactory(GameWorld* world) :
	_world(world)
{}

std::shared_ptr<SimpleGameObject> GameObjectFactory::createBox(const b2Vec2& pos, float angle, const b2Vec2& size, b2BodyType type, const std::string& fileName)
{
	Sprite* sprite = createSprite(fileName, size); 
	
	b2PolygonShape physShape;
	physShape.SetAsBox(size.x / 2, size.y / 2);
	b2Body* body = createBody(type, &physShape, pos, angle);
	
	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);
    
    IGameObject* iobj = obj.get();
    body->SetUserData(iobj);

	return obj;
}

std::shared_ptr<IGameObject> GameObjectFactory::createStaticStone(const b2Vec2 & topLeftCornerPos, float width, const std::string & fileName)
{
	Sprite* sprite = createSprite(fileName);

	Vec2 spriteSize = sprite->getContentSize();
	float scale = width / Convert::toMeters(spriteSize.x);

	sprite->setScale(scale);

	b2Vec2 bodySize = Convert::toMeters(spriteSize * scale);
	b2Vec2 bodyCenter = topLeftCornerPos + b2Vec2(bodySize.x / 2, -bodySize.y / 2);

	b2PolygonShape physShape;
	physShape.SetAsBox(bodySize.x / 2, bodySize.y / 2);
	b2Body* body = createBody(b2BodyType::b2_staticBody, &physShape, bodyCenter, 0);
    
	std::shared_ptr<SimpleGameObject> obj = std::shared_ptr<SimpleGameObject>(new SimpleGameObject(body, sprite, _world));
	_world->addObject(obj);

    IGameObject* iobj = obj.get();
    body->SetUserData(iobj);
    
	return obj;
}

std::shared_ptr<IGameObject> GameObjectFactory::createCircle(const b2Vec2& pos, float angle, float radius, b2BodyType type, const std::string& fileName)
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

std::shared_ptr<Bomb> GameObjectFactory::createBomb(const b2Vec2 &pos, float angle, const b2Vec2 &size)
{
    b2PolygonShape physShape;
    physShape.SetAsBox(size.x / 2, size.y / 2);
    b2Body* body = createSensor(b2BodyType::b2_staticBody, &physShape, pos, angle);
    
    std::shared_ptr<Bomb> obj = std::shared_ptr<Bomb>(new Bomb(body, _world));
    _world->addObject(obj);
    
    IGameObject* ibomb = obj.get();
    body->SetUserData(ibomb);
    
    return obj;
}

std::shared_ptr<AnimationObject> GameObjectFactory::createBombExplosion(const b2Vec2& pos)
{
    Vector<SpriteFrame*> frames;
    
    for (int i = 0; i < 4; ++i)
    {
        std::string fString = "resources/bomb_" + std::to_string(i) + ".png";
        Rect fRect;
        fRect.size = Size(64, 64);
        fRect.origin = Vec2(0, 0);
        SpriteFrame* frame = SpriteFrame::create(fString, fRect);
        
        frames.pushBack(frame);
    }
    
    std::shared_ptr<AnimationObject> animation = std::shared_ptr<AnimationObject>(new AnimationObject(_world, frames, 10, false));
    animation->setPosition(pos);
    _world->addObject(animation);
    
    return animation;
}

b2Body* GameObjectFactory::createBody(b2BodyType type, b2Shape* shape, const b2Vec2& pos, float angle)
{
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position = pos;
	bodyDef.angle = angle;
	bodyDef.linearDamping = 5;
	bodyDef.angularDamping = 5;
	b2Body* body = _world->getPhysics()->CreateBody(&bodyDef);

	b2FixtureDef bodyFixtureDef;
	bodyFixtureDef.shape = shape;
	bodyFixtureDef.density = 1;
	body->CreateFixture(&bodyFixtureDef);

	return body;
}

b2Body* GameObjectFactory::createSensor(b2BodyType type, b2Shape *shape, const b2Vec2 &pos, float angle)
{
    b2BodyDef bodyDef;
    bodyDef.type = type;
    bodyDef.position = pos;
    bodyDef.angle = angle;
    bodyDef.linearDamping = 5;
    bodyDef.angularDamping = 5;
    b2Body* body = _world->getPhysics()->CreateBody(&bodyDef);
    
    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.shape = shape;
    bodyFixtureDef.density = 1;
    bodyFixtureDef.isSensor = true;
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

Sprite* GameObjectFactory::createSprite(const std::string& textureName)
{
	auto sprite = Sprite::create(textureName);
	_world->getGraphics()->addChild(sprite);

	return sprite;
}

void GameObjectFactory::scale(const b2Vec2& size, cocos2d::Sprite * sprite)
{
	Size spriteSize = sprite->getContentSize();

	float x = Convert::toPixels(size.x) / spriteSize.width;
	float y = Convert::toPixels(size.y) / spriteSize.height;

	sprite->setScale(x, y);
}

