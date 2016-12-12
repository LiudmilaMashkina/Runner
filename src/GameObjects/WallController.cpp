#pragma warning(push, 0)
#include <2d/CCNode.h>
#pragma warning(pop)
#include "WallController.h"
#include "GameWorld.h"
#include "WallStone.h"
#include "CollisionCategory.h"
#include "Utils/b2Vec2Operators.h"


USING_NS_CC;

WallController::WallController(GameWorld* wold, const b2Vec2& position) :
_world(wold),
_position(position)
{}

WallController::~WallController()
{}

void WallController::update(float delta)
{
    /*
    for (int i = 0; i < _wStones.size(); ++i)
    {
        std::shared_ptr<WallStone> strongPtr = _wStones[i].lock();
        strongPtr->update(delta);
    }
     */
}

void WallController::addStone(std::weak_ptr<WallStone> wStone)
{
    _wStones.push_back(wStone);
    /*
    std::shared_ptr<WallStone> strongPtr = wStone.lock();
    b2Body* body = strongPtr->getBody();
    _stonesMap[body] = wStone;
     */
}

void WallController::destroyWall(const b2Vec2 &hitPos, float maxHitImpulse)
{
    if (_isDestroyed)
        return;
    
    _isDestroyed = true;
    
    for (int i = 0; i < _wStones.size(); ++i)
    {
        std::shared_ptr<WallStone> strongPtr = _wStones[i].lock();
        if (!strongPtr)
            continue;
        
        auto body = strongPtr->getBody();
        body->SetType(b2BodyType::b2_dynamicBody);
        body->SetLinearDamping(0.1f);
        body->SetAngularDamping(0.1f);
        
        for (b2Fixture* fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext())
        {
            b2Filter filter = fixture->GetFilterData();
            filter.maskBits = CollisionCategory::DefaultCategory;
            fixture->SetFilterData(filter);
        }
    }
    
    struct Callback : public b2RayCastCallback
    {
        Callback(b2Vec2 dir, float maxImp) :
        direction(dir),
        maxImpulse(maxImp)
        {}
        
        virtual float ReportFixture(b2Fixture* fix, const b2Vec2& point,
                                    const b2Vec2& normal, float fraction) override
        {
            float distance = maxRayCast;
            
            auto body = fix->GetBody();
            auto data = body->GetUserData();
            IGameObject* obj = static_cast<IGameObject*>(data);
            
            if (obj->getType() == GameObjectType::WallStone)
            {
                distance = std::min(distance, fraction * maxRayCast);
                float factor = maxImpulse / maxRayCast;
                float curImpulse = distance * factor;
                curImpulse = maxImpulse - curImpulse;
                fix->GetBody()->ApplyLinearImpulse(direction * curImpulse,
                                                   point,
                                                   true);
            }
            
            return 0;
        }
        
        const float maxRayCast = 3.0f;
        b2Vec2 direction = {0, 0};
        const float maxImpulse = 0.0f;
};
    
    
    for (int deg = 0; deg <= 360; deg += 10)
    {
        float angle = deg * (M_PI / 180.f);
        b2Vec2 direction;
        direction.x = cosf(angle);
        direction.y = sinf(angle);
        
        Callback callback(direction, maxHitImpulse);
        
        b2Vec2 destination = hitPos + callback.direction * callback.maxRayCast;
        
        b2Vec2 outgoingPoint = hitPos;
        outgoingPoint += -direction * 0.25;
        
        _world->getPhysics()->RayCast(&callback, outgoingPoint, destination);
    }
    _world->removeObjectLater(this);
}
