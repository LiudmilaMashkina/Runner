#pragma warning(push, 0)
#include <2d/CCSpriteFrame.h>
#pragma warning(pop)

#include "GameObjectFactory.h"
#include "IGameObject.h"
#include "SimpleGameObject.h"
#include "Bomb.h"
#include "Bulb.h"
#include "Grass.h"
#include "AnimationObject.h"
#include "ParticlesObject.h"
#include "Utils/Convert.h"
#include "Particles/ParticlesFactory.h"
#include "Utils/Environment.h"

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

std::shared_ptr<IGameObject> GameObjectFactory::createStaticStone(const b2Vec2 & topLeftCornerPos, float width, const std::string & fileName, float* outHeight)
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
    
    if (outHeight)
        *outHeight = bodySize.y;
    
    int bulbQuantity = Environment::generateIntRand(1, 4);
    
    addBulbs(bulbQuantity, bodySize, topLeftCornerPos, body);
    
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
    b2Body* body = createSensor(b2BodyType::b2_dynamicBody, &physShape, pos, angle);
    
    auto particles = createBombParticles(pos);
    
    std::shared_ptr<Bomb> obj = Bomb::create(body, _world, particles);
    _world->addObject(obj);
    
    IGameObject* ibomb = obj.get();
    body->SetUserData(ibomb);
    
    return obj;
}

std::shared_ptr<Grass> GameObjectFactory::createGrass(const b2Vec2 &pos, float angle, const b2Vec2 &size)
{
    b2PolygonShape physShape;
    physShape.SetAsBox(size.x / 2, size.y / 2);
    
    b2Body* body = createSensor(b2BodyType::b2_dynamicBody, &physShape, pos, angle);
    auto sprite = createSprite("resources/grass_1.png", size);
    auto particles = createGrassParticles(pos, size);
    
    std::shared_ptr<Grass> obj = Grass::create(body, _world, sprite, particles);
    _world->addObject(obj);
    
    particles->setPaused(true);

    IGameObject* igrass = obj.get();
    body->SetUserData(igrass);
    
    return obj;
}

std::shared_ptr<Bulb> GameObjectFactory::createBulb(const b2Vec2 &pos, const b2Vec2 &size)
{
    b2PolygonShape physShape;
    physShape.SetAsBox(size.x / 2, size.y / 2);
    
    b2Body* body = createSensor(b2BodyType::b2_dynamicBody, &physShape, pos, 0);
    auto sprite = createSprite("resources/spongebob.png", size);
    
    std::shared_ptr<Bulb> obj = Bulb::create(body, _world, sprite);
    _world->addObject(obj);
    
    IGameObject* ibulb = obj.get();
    body->SetUserData(ibulb);
    
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

std::shared_ptr<ParticlesObject> GameObjectFactory::createBombParticles(const b2Vec2& pos)
{
    auto system = ParticlesFactory::createBombParticles(_world->getTimeProvider(), _world->getGraphics());
    std::shared_ptr<ParticlesObject> obj = ParticlesObject::create(system, _world) ;
    _world->addObject(obj);

    return obj;
}

std::shared_ptr<ParticlesObject> GameObjectFactory::createGrassParticles(const b2Vec2 &pos, const b2Vec2& diapason)
{
    auto system = ParticlesFactory::createGrassParticles(_world->getTimeProvider(), _world->getGraphics(), diapason);
    std::shared_ptr<ParticlesObject> obj = ParticlesObject::create(system, _world);
    _world->addObject(obj);
    
    return obj;
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

void GameObjectFactory::addBulbs(int quantity, const b2Vec2 &bodySize, const b2Vec2 &topLeftCorner, b2Body *body)
{
    for (; quantity > 0; --quantity)
    {
        int side = Environment::generateIntRand(1, 4);
        b2Vec2 bulbPos = topLeftCorner;
        
        if (side == 1)
        {
            float posX = Environment::generateFloatRand(0.0f, bodySize.x);
            bulbPos.x += posX;
        }
        else if (side == 2)
        {
            bulbPos.x = topLeftCorner.x + bodySize.x;
            float posY = Environment::generateFloatRand(0.0f, bodySize.y);
            bulbPos.y -= posY;
        }
        else if (side == 3)
        {
            float posX = Environment::generateFloatRand(0.0f, bodySize.x);
            bulbPos.x += posX;
            bulbPos.y = topLeftCorner.y - bodySize.y;
        }
        else if (side == 4)
        {
            float posY = Environment::generateFloatRand(0.0f, bodySize.y);
            bulbPos.y -= posY;
        }
        
        float bSize = Environment::generateFloatRand(0.15, 0.4);
        auto bulb = createBulb(bulbPos, b2Vec2(bSize, bSize));
        
        bulb->lightOn(false);
        
        b2WeldJointDef jointDef;
        jointDef.bodyA = body;
        
        auto localForStone = body->GetLocalPoint(bulbPos);
        jointDef.localAnchorA.Set(localForStone.x, localForStone.y);
        auto bulbBody = bulb->getBody();
        (assert(bulbBody));
        jointDef.bodyB = bulbBody;
        jointDef.localAnchorB.Set(0.0f, 0.0f);
        _world->getPhysics()->CreateJoint(&jointDef);
    }
}

void GameObjectFactory::scale(const b2Vec2& size, cocos2d::Sprite * sprite)
{
	Size spriteSize = sprite->getContentSize();

	float x = Convert::toPixels(size.x) / spriteSize.width;
	float y = Convert::toPixels(size.y) / spriteSize.height;

	sprite->setScale(x, y);
}

