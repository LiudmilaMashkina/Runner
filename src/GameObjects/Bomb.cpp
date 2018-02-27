#pragma warning(push, 0)
#include <2d/CCNode.h>
#include <2d/CCSprite.h>
#pragma warning(pop)
#include <set>
#include <math.h>
#include "Bomb.h"
#include "../GameSoundType.h"
#include "../AudioEngine.h"
#include "Hero/Hero.h"
#include "GameWorld.h"
#include "Utils/Convert.h"
#include "Utils/b2Vec2Operators.h"
#include "GameObjectFactory.h"
#include "ParticlesObject.h"
#include "AnimationEngine/IAnimation.h"


USING_NS_CC;

Bomb::Bomb(b2Body* body,
           GameWorld* world, Node* node, IAnimationPtr animation,
           const std::shared_ptr<ParticlesObject>& particles) :
SimpleGameObject::SimpleGameObject(body, node, world),
_animation(animation),
_particles(particles)
{
    update(0);
}

Bomb::~Bomb()
{}

void Bomb::update(float delta)
{
	b2Vec2 bodyPos = _body->GetPosition();
	float bodyAngle = _body->GetAngle();

	_node->setPosition(Convert::toPixels(bodyPos));
	_node->setRotation(Convert::toDegrees(-bodyAngle));
    _particles->setPosition(bodyPos);
    _animation->update(delta);
}

void Bomb::onContactBegin(std::shared_ptr<IGameObject> obj)
{
    if (obj->getType() != GameObjectType::Hero)
        return;
    
    static_cast<Hero*>(obj.get())->collideBomb();
    
    explode(getPosition());
}

void Bomb::drop()
{
    explode(getPosition());
}

void Bomb::explode(const b2Vec2& pos)
{
    struct Callback : public b2RayCastCallback
    {
        Callback(b2Vec2 dir) :
        direction(dir)
        {}
        
        virtual float ReportFixture(b2Fixture* fix, const b2Vec2& point,
                                    const b2Vec2& normal, float fraction) override
        {
            float distance = maxRayCast;
            
            if (!fix->IsSensor())
            {
                distance = std::min(distance, fraction * maxRayCast);
                float factor = maxImpulse / maxRayCast;
                float curImpulse = distance * factor;
                curImpulse = maxImpulse - curImpulse;
                fix->GetBody()->ApplyLinearImpulse(direction * curImpulse,
                                                   point,
                                                   true);
            }
            
            return 1;
        }
        
        const float maxRayCast = 3.0f;
        const float maxImpulse = 10.0f;
        b2Vec2 direction = {0, 0};
    };
    
    b2Vec2 bombPos = getPosition();
    
    for (int deg = 0; deg <= 360; deg += 10)
    {
        float angle = deg * (M_PI / 180.f);
        b2Vec2 direction;
        direction.x = cosf(angle);
        direction.y = sinf(angle);
        
        Callback callback(direction);
        
        b2Vec2 destination = bombPos + callback.direction * callback.maxRayCast;
        
        b2Vec2 outgoingPoint = bombPos;
        outgoingPoint += -direction * 0.25;

        _world->getPhysics()->RayCast(&callback, outgoingPoint, destination);
    }
    
    GameObjectFactory factory(_world);
    
    float scale = getScale();
    AudioEngine::getInstance()->playSound(GameSoundType::Bomb);
    auto explosion = factory.createBombExplosion(getPosition(), scale);
    
    
    _particles->setPaused(true);
    _world->removeObjectLater(this);
}
