//
//  FallState.cpp
//  Wanderer
//
//  Created by Luda on 29/12/15.
//
//

#include "FallState.h"
#include "AnimationEngine/AnimationFactory.h"
#include "Utils/Convert.h"
#include "Utils/b2Utils.h"
#include "GameWorld.h"
#include "AnimationEngine/AnimationEngine.h"
#include "Utils/b2Vec2Operators.h"

FallState::FallState(GameWorld* world,
                     HeroData* data) :
_world(world),
_data(data)
{}

void FallState::onEnter()
{
    _data->animationEngine->goToAnimationGroup("fall");
}

HeroStateId FallState::update(float delta)
{
    b2Vec2 pos = Convert::toMeters(_data->node->getPosition());
    
    float hitDistance = b2Utils::raycast(_world->getPhysics(),
                                             b2Vec2(pos.x, pos.y + 0.5),
                                             b2Vec2(0, -1));
    
    if (hitDistance <= 1)
    {
        return HeroStateId::Run;
    }
    else
    {   
        pos.x += _data->velocity.x * delta;
        pos.y += _data->velocity.y * delta + _data->acceleration.y * delta * delta / 2;
        _data->node->setPosition(Convert::toPixels(pos));

        _data->velocity += _data->acceleration * delta;
    }
    
    return getStateId();
}

HeroStateId FallState::onTap()
{
    if (_data->canAttack)
        return HeroStateId::Attack;
    else
        return getStateId();
}

void FallState::onExit()
{
    
}

HeroStateId FallState::getStateId() const
{
    return HeroStateId::Fall;
}

