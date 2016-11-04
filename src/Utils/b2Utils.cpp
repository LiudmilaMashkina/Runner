#include "b2Utils.h"
#include "Utils/b2Vec2Operators.h"

namespace
{
    const float MaxRaycastDistance = 1000;
}

float b2Utils::raycast(const std::shared_ptr<b2World> &b2world, const b2Vec2 &source, const b2Vec2 &direction)
{
    struct Callback : public b2RayCastCallback
    {
        Callback() : distance(std::numeric_limits<float>::max()) {}
        
        virtual float ReportFixture(b2Fixture* fixture, const b2Vec2& point,
                                      const b2Vec2& normal, float fraction) override
        {
            if (!fixture->IsSensor())
                distance = std::min(distance, fraction * MaxRaycastDistance);
            return 1;
        }
        
        float distance;
    };
    
    Callback callback;
    
    b2Vec2 normalizedDirection = direction;
    normalizedDirection.Normalize();
    b2Vec2 destination = source + normalizedDirection * MaxRaycastDistance;
    b2world->RayCast(&callback, source, destination);
    
    return callback.distance;
}
