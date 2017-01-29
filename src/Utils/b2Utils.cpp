#include "b2Utils.h"
#include "Utils/b2Vec2Operators.h"

namespace
{
    const float MaxRaycastDistance = 1000;
}

float b2Utils::raycast(const std::shared_ptr<b2World> &b2world, const b2Vec2 &source, const b2Vec2 &direction)
{
    return raycastImpl(b2world, source, direction, nullptr);
}

float b2Utils::raycast(const std::shared_ptr<b2World> &b2world, const b2Vec2 &source, const b2Vec2 &direction, const b2Filter &filter)
{
    return raycastImpl(b2world, source, direction, &filter);
}

float b2Utils::raycastImpl(const std::shared_ptr<b2World> &b2world, const b2Vec2 &source, const b2Vec2 &direction, const b2Filter *filter)
{
    struct Callback : public b2RayCastCallback
    {
        Callback(const b2Filter* filter) :
            _distance(std::numeric_limits<float>::max()),
            _filter(filter)
        {}
        
        virtual float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                      const b2Vec2& normal, float fraction) override
        {
            if (fixture->IsSensor())
                return 1;
            
            b2Filter filter = fixture->GetFilterData();
            if (_filter != nullptr)
            {
                bool collide = (_filter->maskBits & filter.categoryBits) > 0 &&
                               (_filter->categoryBits & filter.maskBits) > 0;
                if (!collide)
                    return 1;
            }
 
            _distance = std::min(_distance, fraction * MaxRaycastDistance);
            return 1;
        }
        
        float _distance;
        const b2Filter* _filter;
    };
    
    Callback callback(filter);
    
    b2Vec2 normalizedDirection = direction;
    normalizedDirection.Normalize();
    b2Vec2 destination = source + normalizedDirection * MaxRaycastDistance;
    b2world->RayCast(&callback, source, destination);
    
    return callback._distance;
}
